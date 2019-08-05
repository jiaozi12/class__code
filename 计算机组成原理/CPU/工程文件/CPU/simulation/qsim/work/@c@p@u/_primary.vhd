library verilog;
use verilog.vl_types.all;
entity CPU is
    port(
        clk             : in     vl_logic;
        clr             : in     vl_logic;
        address         : out    vl_logic_vector(7 downto 0);
        result          : out    vl_logic_vector(15 downto 0);
        c               : out    vl_logic;
        z               : out    vl_logic;
        n               : out    vl_logic;
        ov              : out    vl_logic
    );
end CPU;
