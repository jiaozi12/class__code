library verilog;
use verilog.vl_types.all;
entity Instruction_system_vlg_check_tst is
    port(
        inst            : in     vl_logic_vector(47 downto 0);
        result          : in     vl_logic_vector(15 downto 0);
        sampler_rx      : in     vl_logic
    );
end Instruction_system_vlg_check_tst;
