

OPENCV_INSTALL_DIR = /home/diego/install/opencv/

export LD_LIBRARY_PATH=$(OPENCV_INSTALL_DIR)/lib:/home/diego/install/script/lib
#export LD_LIBRARY_PATH=$(OPENCV_INSTALL_DIR)/lib:/home/diego/script/lib



RocAll:
	#rm compRoc
	gcc compRoc.cpp -o compRoc -D__OPENCV__ -I$(OPENCV_INSTALL_DIR)/include/ -L$(OPENCV_INSTALL_DIR)/lib -lopencv_highgui -lopencv_core -lstdc++ -lopencv_imgproc -lm -I/home/diego/script/include -L/home/diego/script/lib -lvisiongl -I/opt/AMDAPP/include

compMetodoFuzzy:
	#rm metodoFuzzy
	g++ metodoFuzzy.cpp -o metodoFuzzy -D__OPENCV__ -I$(OPENCV_INSTALL_DIR)/include/ -L$(OPENCV_INSTALL_DIR)/lib -lopencv_highgui -lopencv_core -lopencv_imgproc -lm -I/home/diego/script/include -L/home/diego/script/lib -lvisiongl -I/opt/AMDAPP/include

#1 2 3 5 6 9
#3 5 7 9
#3 5 7 9
#1 2 3 4
#x4 x5 x6 
runAll:
	 for number in 9; do \
	   for tam in 3 5 7 9; do \
	     for bh in 2; do \
	       for jan1 in 3 5 7 9; do \
	  	  for val1 in 1 2 3 4; do \
		     for ts in 3.0 4.0 5.0; do \
	      	          #./metodoFuzzy $$number entrada.txt $$tam $$bh $$jan1 $$jan1 $$val1 $$val1 $$ts;  \
			  #./compRoc diretorio.txt $$number $$tam $$bh $$jan1 $$jan1 $$val1 $$val1 $$ts; \
			  #./metodoFuzzy $$number entradaSTARE.txt $$tam $$bh $$jan1 $$jan1 $$val1 $$val1 $$ts;  \
	      	          #./compRoc diretorioSTARE1.txt $$number $$tam $$bh $$jan1 $$jan1 $$val1 $$val1 $$ts "Arquivos/STARE/list1.txt"; \
			  #./compRoc diretorioSTARE2.txt $$number $$tam $$bh $$jan1 $$jan1 $$val1 $$val1 $$ts "Arquivos/STARE/list2.txt"; \
			  #./metodoFuzzy $$number "Entradas/entradaDRIVE.txt" $$tam $$bh $$jan1 $$val1 $$ts;  \
			  #./compRoc "Diretorios/diretorioDRIVE.txt" $$number $$tam $$bh $$jan1 $$val1 $$ts "Resultados/Lista/listaDRIVE.txt"; \
			  #./metodoFuzzy $$number "Entradas/entradaHRF.txt" $$tam $$bh $$jan1 $$val1 $$ts;  \
			  #./compRoc "Diretorios/diretorioHRF.txt" $$number $$tam $$bh $$jan1 $$val1 $$ts "Resultados/Lista/listaHRF.txt"; \
			  ./metodoFuzzy $$number "Entradas/entradaSTARE.txt" $$tam $$bh $$jan1 $$val1 $$ts;  \
			  ./compRoc "Diretorios/diretorioSTARE_1.txt" $$number $$tam $$bh $$jan1 $$val1 $$ts "Resultados/Lista/listaSTARE_1.txt"; \
			  ./compRoc "Diretorios/diretorioSTARE_2.txt" $$number $$tam $$bh $$jan1 $$val1 $$ts "Resultados/Lista/listaSTARE_2.txt"; \
	      	     done \
	           done \
	       done \
	     done \
	   done \
	 done


