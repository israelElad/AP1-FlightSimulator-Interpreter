cmake_minimum_required(VERSION 3.13)
project(ap3)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(ap3 main.cpp OpenDataServerCommand.cpp Expression.cpp Expression.h ExpressionUtils.cpp ExpressionUtils.h OpenDataServerCommand.h main.cpp DataReaderServer.cpp DataReaderServer.h Command.h ConnectCommand.cpp ConnectCommand.h VarCommand.cpp VarCommand.h BindCommand.cpp BindCommand.h WhileCommand.cpp WhileCommand.h PrintCommand.cpp PrintCommand.h EqualCommand.cpp EqualCommand.h DataCommands.cpp DataCommands.h Expression.h DataVars.cpp DataVars.h DataWriterClient.cpp DataWriterClient.h IfCommand.cpp IfCommand.h DataBinds.cpp DataBinds.h SleepCommand.cpp SleepCommand.h EntercCommand.cpp EntercCommand.h ConditionParser.cpp ConditionParser.h TextAnalyzer.cpp TextAnalyzer.h)