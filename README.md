# BEST_Lab1 - "Let there be light"

## A. Introduction

<p align="justify"> Le but de ce tp est de développer une première application basique utilisant le co-design sur la carte DE-10 Lite. Cette application va nous permettre de réaliser un flow de conception complet (Hardware et Software) en utilisant les différents outils de la conception conjointe. L'application consiste à mettre en œuvre un chenillard, c’est-à-dire d’allumer les 10 leds de la carte lors de l’appuie sur un bouton poussoir. La vitesse du chenillard varie grâce à 4 switches. </p>

## B. System architecture

### Flow Hardware

<p align="justify"> La première des choses à faire est de crée un projet vierge sous Quartus. Ensuite, j’ouvre Platform Designer et j’ajoute tous les blocs IP dont j’ai besoin pour créer l’application. Les différents blocs IP sont les suivants : </p>

* **RAM** (taille = 40960 bytes)
* **NIOS2**
* **JTAG-UART** (pour le debug)
* **PIO** pour le contrôle des leds (width = 10 bits)
* **PIO** pour le bonton poussoir de trigger (width = 1 bits, utilisation d'une interruption) => le deuxième bouton poussoir de la carte sera pour le reset
* **PIO** pour les switches de vitesse (width = 4 bits, utilisation d'une interruption)

Les blocs IP sont interfacés de la manière suivante :

![image](https://user-images.githubusercontent.com/121948093/211756377-085fadfe-438f-4b38-be60-8792a0d9ff08.png)

<p align="justify"> Une fois avoir décrit mon système sous Qsys je génère le HDL et je vais sous Quartus pour créer mon top-level VHDL. Dans ce fichier VHDL, je connecte mes différents signaux afin que mes PIOs soient directement connectés à des broches physiques de la carte. Après avoir réaliser un premier Analysis & Synthesis j'assigne mes différentes pins en me référant à la documentation de la carte.</p>

[voir .qsf](https://github.com/ESN2022/BEST_Lab1/blob/main/lab1.qsf)

<p align="justify">Enfin, je compile mon design sous Quartus et je programme le FPGA. </p>

### Flow software

<p align="justify"> La deuxième étape est de générer le BSP et d'écrire un code en C décrivant le comportement de notre NIOS. Pour cela j'utilise le nios2 command shell et je déroule le flow software en utilisant les différentes commandes du cours. </p>

<p align="justify"> L'allumage des leds pour le chenillard est gérer par des décalages de bits. Le trigger du chenillard est une interruption sur le bouton poussoir. Le changement de la vitesse du chenillard est déclanché par une interruption sur les switches et la vitesse est égale à la valeur des 4 bits des switches multiplié par une constante choisit arbitrairement (ici 10000). Lorsque tous les switches sont à 0, il y a une valeur de vitesse par défaut. </p>

<p align="justify"> La déclaration d'une interruption est la suivante :</p>

Dans le main :

- On active active l'interruption que l'on souhaite sur le périphérique avec un masque puis on spécifie quel bit il faudra clear dans la routine. 

```
IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PUSH_BUTTONS_BASE, 0b1);
IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSH_BUTTONS_BASE, 0b1);
```

- Ensuite on enregistre l'interruption en renseignant les différents paramètres de la fonction qui se trouvent dans le **system.h** et le nom de la routine (irqhandler_push_button ici).

```
alt_ic_isr_register(PUSH_BUTTONS_IRQ_INTERRUPT_CONTROLLER_ID,PUSH_BUTTONS_IRQ, (void*)irqhandler_push_button, NULL, 0);
```

Dans la routine d'interruption :

- On écrit le code que l'ISR doit effectué et on oublie pas de clear notre interruption à la fin.

```
IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSH_BUTTONS_BASE, 0b1);
```

## C. Progress, results

<p align="justify"> La première version de mon code C faisait fonctionner le chenillard en utilisant uniquement du polling et les deux BPs.</p>

<p align="justify"> La deuxième version intégrait deux interruptions (celle du BP et celle des switches). Le chenillard est alors fonctionnel en respectant le cahier des charges. </p>

![image](https://user-images.githubusercontent.com/121948093/211770384-90cc7a3a-b128-4503-8294-4df6f601e1bc.png)

## D. Conclusion

<p align="justify"> Ce premier TP m'a permis de créer ma première application intégrant du co-design. J'ai notamment piloté les leds et lu les valeurs des switches et du BP, de la carte DE10-Lite, grâce au NIOS. J'ai appris à utiliser les différents outils et à dérouler un flow de conception complet. La principale difficulté du tp a été la déclaration des interruptions. En effet, on ne pouvait pas utiliser directement les commandes du cours car on avait une interrupt API différente dans notre cas et la structure des fonctions à utiliser l'était aussi. Il a donc fallu vérifié dans la datasheet des interruptions du NIOS et dans le system.h le type d'interrupt API et comment déclarer une interruption. </p>

```
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
```
