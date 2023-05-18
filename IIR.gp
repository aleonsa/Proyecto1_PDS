# GRAFICACION EN GNUPLOT

#set term corel


set autoscale
#set multiplot layout 2,2 rowsfirst
set grid
set style data lines

#------------- Graf 1 ----------------
set title "Sine Function with IIR"
#unset label
set xlabel   "n"
set ylabel   "x(n)"
plot  "iir.dat"
unset xlabel
unset ylabel
unset title