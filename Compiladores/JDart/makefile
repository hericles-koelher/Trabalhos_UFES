COMPILER_SRC=compiler_src
RUNTIME_SRC=runtime_src
RUNTIME_CLASS_DIR=$(RUNTIME_SRC)/files
COMPILER_CLASS_DIR=$(COMPILER_SRC)/files
ANTLR4=tools/antlr-4.9.1-complete.jar
ASM=tools/asm-9.1.jar
RUNTIME=tools/runtime.jar
PACKAGE=Dart
COMPILER_PACKAGE_DIR=$(COMPILER_SRC)/$(PACKAGE)
JAVA_FILES=$(shell find compiler_src/ -name "*.java")
RUNTIME_FILES=$(shell find runtime_src/ -name "*.java")
RUNTIME_CLASS_FILES=$(shell find runtime_src/ -name "*.class")

all: Classes

#Criação dos arquivos .class
Classes: Runtime Dart
	javac -d $(COMPILER_CLASS_DIR) -cp $(ANTLR4):$(ASM):$(RUNTIME) $(JAVA_FILES)

#Codigo do Scanner+Parser
Dart:
	java -jar $(ANTLR4) -visitor -package $(PACKAGE) -o $(COMPILER_PACKAGE_DIR) -Xexact-output-dir $(COMPILER_SRC)/Dart.g4

Runtime:
	javac -d $(RUNTIME_CLASS_DIR) $(RUNTIME_FILES)
	jar -cf0 $(RUNTIME) -C $(RUNTIME_CLASS_DIR) .
# Caraca vei esse ponto faz total diferença, MDS.

clean:
	rm -rf $(COMPILER_CLASS_DIR) $(RUNTIME_CLASS_DIR) output $(COMPILER_SRC)/Dart
#Testes

run:
	java -cp $(COMPILER_CLASS_DIR):$(ANTLR4):$(ASM):$(RUNTIME) Main dart_sample_code/correct/4.dart
	dot -Tpdf ast1.dot -o ast1.pdf

run_java:
	 java -cp tools/runtime.jar:output/ Main