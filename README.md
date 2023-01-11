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
* **PIO** pour le bonton poussoir de trigger (width = 1 bits)
* **PIO** pour les switches de vitesse (width = 4 bits)

Les blocs IP sont interfacés de la manière suivante :

![image](https://user-images.githubusercontent.com/121948093/211756377-085fadfe-438f-4b38-be60-8792a0d9ff08.png)

<p align="justify"> Une fois avoir décrit mon système sous Qsys je génère le HDL et je vais sous Quartus pour créer mon top-level VHDL. Dans ce fichier VHDL, je connecte mes différents signaux afin que mes PIOs soient directement connectés à des broches physiques de la carte. Après avoir réaliser un premier Analysis & Synthesis j'assigne mes différentes pins en me référant à la documentation de la carte.</p>

[voir .qsf](https://github.com/ESN2022/BEST_Lab1/blob/main/lab1.qsf)

<p align="justify">Enfin, je compile mon design sous Quartus. </p>



## C. Progress, results

<p align="justify"> </p>

## D. Conclusion

<p align="justify"> </p>
