# GRAFICACION EN GNUPLOT

#set term corel


set autoscale
#set multiplot layout 2,2 rowsfirst
set grid
set style data lines

#------------- Graf 1 ----------------
set title "Autocorrelation of x(n)"
#unset label
set xlabel   "n"
set ylabel   "Rxx(n)"
plot  "auto.dat"
unset xlabel
unset ylabel
unset title