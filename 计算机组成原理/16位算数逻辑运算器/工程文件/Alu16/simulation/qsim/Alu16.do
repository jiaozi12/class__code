onerror {quit -f}
vlib work
vlog -work work Alu16.vo
vlog -work work Alu16.vt
vsim -novopt -c -t 1ps -L cyclone_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.Alu16_vlg_vec_tst
vcd file -direction Alu16.msim.vcd
vcd add -internal Alu16_vlg_vec_tst/*
vcd add -internal Alu16_vlg_vec_tst/i1/*
add wave /*
run -all
