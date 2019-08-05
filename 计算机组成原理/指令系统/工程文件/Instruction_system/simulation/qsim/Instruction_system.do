onerror {quit -f}
vlib work
vlog -work work Instruction_system.vo
vlog -work work Instruction_system.vt
vsim -novopt -c -t 1ps -L cyclone_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.Instruction_system_vlg_vec_tst
vcd file -direction Instruction_system.msim.vcd
vcd add -internal Instruction_system_vlg_vec_tst/*
vcd add -internal Instruction_system_vlg_vec_tst/i1/*
add wave /*
run -all
