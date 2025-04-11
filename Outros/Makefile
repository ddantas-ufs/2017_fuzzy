

OPENCV_INSTALL_DIR = /home/diego/install/opencv/
METODO = 6

export LD_LIBRARY_PATH=$(OPENCV_INSTALL_DIR)/lib:/home/diego/install/script/lib


fuzzy:
	gcc fuzzy.cpp -o fuzzy -I$(OPENCV_INSTALL_DIR)/include/ -L$(OPENCV_INSTALL_DIR)/lib -lopencv_highgui -lopencv_core -lstdc++ -lopencv_imgproc -lm -I/home/diego/script/include -L/home/diego/script/lib -lvisiongl -I/opt/AMDAPP/include

runfuzzy:
	./fuzzy $(METODO) entrada.txt
#1 2 3 4 5 6 7 8 9

runfuzzyAll:
	 for number in 1 2 3 4 5 6 7 8 9; do \
	    for tam in 5; do \
		for bh in 1; do \
		  for ts in 8; do \
	      	    ./fuzzy $$number entrada.txt $$tam $$bh $$ts;  \
	      	    ../Comparacao/comp ../Comparacao/diretorio.txt \
	      	    mv Arquivos/*.tif Arquivos/$$number; \
		    mv Comparacao.txt Arquivos/$$number; \
		  done \
		done \
	    done \
	done 

clean:
	rm fuzzy

all:
	#rm fuzzy
	gcc fuzzy.cpp -o fuzzy -I$(OPENCV_INSTALL_DIR)/include/ -L$(OPENCV_INSTALL_DIR)/lib -lopencv_highgui -lopencv_core -lstdc++ -lopencv_imgproc -lm -I/home/diego/script/include -L/home/diego/script/lib -lvisiongl -I/opt/AMDAPP/include
	./fuzzy $(METODO) entrada.txt 5 2 4.0
	./compRoc ../Comparacao/diretorio.txt
#	../Comparacao/comp ../Comparacao/diretorio.txt


compMetodoFuzzy:
	#rm metodoFuzzy
	gcc metodoFuzzy.cpp -o metodoFuzzy -I$(OPENCV_INSTALL_DIR)/include/ -L$(OPENCV_INSTALL_DIR)/lib -lopencv_highgui -lopencv_core -lstdc++ -lopencv_imgproc -lm -I/home/diego/script/include -L/home/diego/script/lib -lvisiongl -I/opt/AMDAPP/include

compTest:
	gcc metodo.cpp -o metodo -I$(OPENCV_INSTALL_DIR)/include/ -L$(OPENCV_INSTALL_DIR)/lib -lopencv_highgui -lopencv_core -lstdc++ -lopencv_imgproc -lm -I/home/diego/script/include -L/home/diego/script/lib -lvisiongl -I/opt/AMDAPP/include

runTest:
	for number in 1 2 3 5 6 9; do \
	  for tam in 5; do \
	    ./metodo $$number $$tam "Arquivos/Imagens/";  \
	  done \
	done


runAll:
	 for number in 1 2 3 5 6 9; do \
	   for tam in 3 5 7; do \
	     for bh in 2; do \
	       for jan1 in 3 5 7; do \
	  	# for jan2 in 3; do \
		   for val1 in 1 2 3 4; do \
		    # for val2 in 1; do \
	 	       for ts in 3.0 4.0 5.0; do \
	      	          #./metodoFuzzy $$number entrada.txt $$tam $$bh $$jan1 $$jan1 $$val1 $$val1 $$ts;  \
			  #./compRoc diretorio.txt $$number $$tam $$bh $$jan1 $$jan1 $$val1 $$val1 $$ts; \
			  #./metodoFuzzy $$number entradaSTARE.txt $$tam $$bh $$jan1 $$jan1 $$val1 $$val1 $$ts;  \
	      	          #./compRoc diretorioSTARE1.txt $$number $$tam $$bh $$jan1 $$jan1 $$val1 $$val1 $$ts "Arquivos/STARE/list1.txt"; \
			  #./compRoc diretorioSTARE2.txt $$number $$tam $$bh $$jan1 $$jan1 $$val1 $$val1 $$ts "Arquivos/STARE/list2.txt"; \
			  ./metodoFuzzy $$number entrada.txt $$tam $$bh $$jan1 $$jan1 $$val1 $$val1 $$ts "2.0";  \
			  ./compRoc diretorio.txt $$number $$tam $$bh $$jan1 $$jan1 $$val1 $$val1 $$ts "Arquivos/listDiv2.txt"; \
			  ./metodoFuzzy $$number entrada.txt $$tam $$bh $$jan1 $$jan1 $$val1 $$val1 $$ts "4.0";  \
	      	          ./compRoc diretorio.txt $$number $$tam $$bh $$jan1 $$jan1 $$val1 $$val1 $$ts "Arquivos/listDiv4.txt"; \
	      	     #  done \
		   #  done \
		   done \
	         done \
	       done \
	     done \
	   done \
	 done


# 14min 2min 5
runmetodoFuzzyAll:
	 for number in 9; do \
	    for tam in 3; do \
		for bh in 2; do \
		  for ts in 4.0; do \
	      	     ./metodoFuzzy $$number entrada.txt $$tam $$bh $$ts;  \
	      	     #mv Arquivos/$$number/$$tam/$$bh/$$ts/*.tif Arquivos/; \
		        #../Comparacao/comp ../Comparacao/diretorio.txt; \
		      	#./compRoc ../Comparacao/diretorio.txt; \
			./compRoc diretorio.txt; \
	      	     #mv Arquivos/*.tif Arquivos/$$number/$$tam/$$bh/$$ts; \
		     #mv Arquivos/Comparacao01-40.txt Arquivos/$$number/$$tam/$$bh/$$ts; \
		     #mv Arquivos/ResultRoc01-40.txt Arquivos/$$number/$$tam/$$bh/$$ts; \
		  done \
		done \
	    done \
	done

RocAll:
	#rm compRoc
	gcc compRoc.cpp -o compRoc -I$(OPENCV_INSTALL_DIR)/include/ -L$(OPENCV_INSTALL_DIR)/lib -lopencv_highgui -lopencv_core -lstdc++ -lopencv_imgproc -lm -I/home/diego/script/include -L/home/diego/script/lib -lvisiongl -I/opt/AMDAPP/include

#gcc ../Comparacao/comp.cpp -o ../Comparacao/comp -I$(OPENCV_INSTALL_DIR)/include/ -L$(OPENCV_INSTALL_DIR)/lib -lopencv_highgui -lopencv_core -lstdc++ -lopencv_imgproc -lm -I/home/diego/script/include -L/home/diego/script/lib -lvisiongl -I/opt/AMDAPP/include	
#	./compRoc ../Comparacao/diretorio.txt

PsnrAll:
	gcc compPSNR.cpp -o compPSNR -I$(OPENCV_INSTALL_DIR)/include/ -L$(OPENCV_INSTALL_DIR)/lib -lopencv_highgui -lopencv_core -lstdc++ -lopencv_imgproc -lm -I/home/diego/script/include -L/home/diego/script/lib -lvisiongl -I/opt/AMDAPP/include
	./compPSNR ../Comparacao/diretorio.txt

metodoAltAll:
	#rm metodoAlt
	gcc metodoAlt.cpp -o metodoAlt -I$(OPENCV_INSTALL_DIR)/include/ -L$(OPENCV_INSTALL_DIR)/lib -lopencv_highgui -lopencv_core -lstdc++ -lopencv_imgproc -lm -I/home/diego/script/include -L/home/diego/script/lib -lvisiongl -I/opt/AMDAPP/include
	./metodoAlt 9 entrada.txt

CompAll:
	#rm compRoc
	gcc ../Comparacao/comp.cpp -o ../Comparacao/comp -I$(OPENCV_INSTALL_DIR)/include/ -L$(OPENCV_INSTALL_DIR)/lib -lopencv_highgui -lopencv_core -lstdc++ -lopencv_imgproc -lm -I/home/diego/script/include -L/home/diego/script/lib -lvisiongl -I/opt/AMDAPP/include


