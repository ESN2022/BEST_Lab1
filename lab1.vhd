library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity lab1 is
    port(
        clk : in std_logic := '0';
		  push_button : in std_logic_vector(1 downto 0) := (others => '0');
        reset_n : in std_logic :='0';
		  led : out std_logic_vector(9 downto 0);
		  switch : in std_logic_vector(3 downto 0) := (others => '0')
		  );
end entity;

architecture rtl of lab1 is
    component lab1_sys is
        port (
            clk_clk                                 : in  std_logic                    := 'X';             -- clk
            leds_external_connection_export         : out std_logic_vector(9 downto 0);                    -- export
            push_buttons_external_connection_export : in  std_logic_vector(1 downto 0) := (others => 'X'); -- export
            reset_reset_n                           : in  std_logic                    := 'X';              -- reset_n
				switches_external_connection_export     : in  std_logic_vector(3 downto 0) := (others => 'X')  -- export
        );
    end component lab1_sys;

begin
    u0 : component lab1_sys
        port map (
            clk_clk                                 => clk,                                 --                              clk.clk
            leds_external_connection_export         => led,         --         leds_external_connection.export
            push_buttons_external_connection_export => push_button, -- push_buttons_external_connection.export
            reset_reset_n                           => reset_n,                            --                            reset.reset_n
				switches_external_connection_export     => switch      --     switches_external_connection.export
        );
          
end architecture;
