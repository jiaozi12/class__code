library verilog;
use verilog.vl_types.all;
entity Instruction_system is
    port(
        choose          : in     vl_logic;
        addr            : in     vl_logic_vector(11 downto 0);
        result          : out    vl_logic_vector(15 downto 0);
        inst            : out    vl_logic_vector(47 downto 0)
    );
end Instruction_system;
