gpp = g++
prom = annulus
deps = $(shell find ./src -name "*.hpp")
src = $(shell find ./src -name "*.cpp")
objdir = ./bin/
obj = $(src:%.cpp=%.o) 

$(prom): $(obj)
	$(gpp) -o $(objdir)$(prom) $(addprefix $(objdir), $(notdir $(obj))) -O2
	./bin/$(prom)

%.o: %.cpp $(deps)
	$(gpp) -c $< -o $(addprefix $(objdir), $(notdir $@)) -O2

clean:
	rm -rf $(objdir)/*
