# GRAFICACION EN GNUPLOT

#set term corel
set output  "PDS_1.eps"

set autoscale
set multiplot layout 2,2 rowsfirst
set grid
set style data lines

#------------- Graf 1 ----------------
set title "Sine Function"
#unset label
set xlabel   "n"
set ylabel   "x(n)"
plot  "sin.dat"
unset xlabel
unset ylabel
unset title

#------------- Graf 2 ----------------
set title "Sine Func. with noise<5dB added"
# unset label
set xlabel   "n"
set ylabel   "x(n)"
plot  "sinNoise.dat"
unset xlabel
unset ylabel
unset title

#------------- Graf 3 ----------------
set title "Gaussian Window"
# unset label
set xlabel   "n"
set ylabel   "x(n)"
set autoscale 
plot  "gaussWindow.dat"

unset xlabel
unset ylabel
unset title

#------------- Graf 4 ----------------
set title "Convolution"
# unset label
set xlabel   "n"
set ylabel   "x(n)"
set xrange[0:10000] 
plot  "conv.dat"

unset xlabel
unset ylabel
unset title

#pause(3)
#unset multiplot

#
