all:
	gcc -o collatz collatz.cpp -lstdc++
	git add *
	git commit -a -m 'Commit'
	git push
	echo "______________________________________________________________________________________" >> highscores.txt
	
