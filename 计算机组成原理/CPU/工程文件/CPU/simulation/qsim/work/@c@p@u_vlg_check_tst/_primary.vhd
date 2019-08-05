library verilog;
use verilog.vl_types.all;
entity CPU_vlg_check_tst is
    port(
        address         : in     vl_logic_vector(7 downto 0);
        c               : in     vl_logic;
        n               : in     vl_logic;
        ov              : in     vl_logic;
        result          : in     vl_logic_vector(15 downto 0);
        z               : in     vl_logic;
        sampler_rx      : in     vl_logic
    );
end CPU_vlg_check_tst;
