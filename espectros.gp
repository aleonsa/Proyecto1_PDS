# GRAFICACION EN GNUPLOT

#set term corel


set autoscale
set multiplot layout 2,2 rowsfirst
set grid
set style data lines

#------------- Graf 1 ----------------
set title "Spectrum of x(n)"
#unset label
#set xlabel   "n"
#set ylabel   "x(n)"
plot  "esp_sinNoise.dat"
unset xlabel
unset ylabel
unset title

#------------- Graf 2 ----------------
set title "Spectrum of Gaussian Window"
# unset label
#set xlabel   "n"
#set ylabel   "x(n)"
plot  "esp_gaussWindow.dat"
unset xlabel
unset ylabel
unset title

#------------- Graf 3 ----------------
set title "Spectrum of Convolution"
# unset label
#set xlabel   "n"
#set ylabel   "x(n)"
set autoscale 
plot  "esp_conv.dat"

unset xlabel
unset ylabel
unset title

#------------- Graf 4 ----------------
set title "Spectrum of Autocorrelation"
# unset label
#set xlabel   "n"
#set ylabel   "x(n)"
#set xrange[0:10000] 
plot  "esp_auto.dat"

unset xlabel
unset ylabel
unset title

#pause(3)
#unset multiplot

#
