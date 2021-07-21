reset
set xtic 0,500;
set ytic 0,50;
set terminal png size 1024,768

set output sprintf("./Convergence.png")

plot "SA.txt" ps 1.0 pt 14  lc rgb '#778da9' 

set output
