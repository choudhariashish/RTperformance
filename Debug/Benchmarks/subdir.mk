################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Benchmarks/bs.cpp \
../Benchmarks/jfdctint.cpp \
../Benchmarks/lms.cpp \
../Benchmarks/matmult.cpp \
../Benchmarks/sqrt.cpp 

OBJS += \
./Benchmarks/bs.o \
./Benchmarks/jfdctint.o \
./Benchmarks/lms.o \
./Benchmarks/matmult.o \
./Benchmarks/sqrt.o 

CPP_DEPS += \
./Benchmarks/bs.d \
./Benchmarks/jfdctint.d \
./Benchmarks/lms.d \
./Benchmarks/matmult.d \
./Benchmarks/sqrt.d 


# Each subdirectory must supply rules for building sources it contributes
Benchmarks/%.o: ../Benchmarks/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


