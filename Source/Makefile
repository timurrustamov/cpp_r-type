CC	=	g++
RM	=	rm -f

SRC_SERV	=		serv_test.cpp			\
				System/Animation.cpp		\
				System/RTypeException.cpp	\
				System/ResourcesBank.cpp	\
				System/window.cpp		\
				GameEngine/LinuxSocket.cpp	\
				GameEngine/GameData.cpp		\
				GameEngine/Level.cpp		\
				GameEngine/OnLevel.cpp		\
				GameEngine/MutexVault.cpp	\
				GameEngine/ISocket.cpp		\
				GameEngine/Packet.cpp		\
				GameEngine/Rsa.cpp		\
				GameEngine/BBException.cpp	\
				GameEngine/Geometry.cpp         \
				GameEngine/Object.cpp           \
				GameEngine/Player.cpp           \
				GameEngine/QuadTree.cpp         \
				GameEngine/Rocket.cpp           \
				GameEngine/SerializedObject.cpp \
				GameEngine/Snapshot.cpp         \
				GameEngine/Timer.cpp            \
				GameEngine/WallOfPain.cpp       \
				GameEngine/World.cpp 		\
				GameEngine/GameRoom.cpp		\
				GameEngine/User.cpp		\
				GameEngine/Explosion.cpp	\
				GameEngine/Instruction.cpp	\
				GameEngine/RTypeServer.cpp	

OBJ_SERV	=	$(SRC_SERV:.cpp=.o)

SRC_CLIENT	=	clie_test.cpp			\
				System/Animation.cpp		\
				System/RTypeException.cpp	\
				System/ResourcesBank.cpp	\
				System/window.cpp		\
				GameEngine/LinuxSocket.cpp	\
				GameEngine/GameData.cpp		\
				GameEngine/Level.cpp		\
				GameEngine/OnLevel.cpp		\
				GameEngine/MutexVault.cpp	\
				GameEngine/ISocket.cpp		\
				GameEngine/Packet.cpp		\
				GameEngine/Rsa.cpp		\
				GameEngine/BBException.cpp	\
				GameEngine/Geometry.cpp         \
				GameEngine/Object.cpp           \
				GameEngine/Player.cpp           \
				GameEngine/QuadTree.cpp         \
				GameEngine/Rocket.cpp           \
				GameEngine/SerializedObject.cpp \
				GameEngine/Snapshot.cpp         \
				GameEngine/Timer.cpp            \
				GameEngine/WallOfPain.cpp       \
				GameEngine/World.cpp 		\
				GameEngine/GameRoom.cpp		\
				GameEngine/User.cpp		\
				GameEngine/Explosion.cpp	\
				GameEngine/Instruction.cpp	\
				GameEngine/RTypeServer.cpp

OBJ_CLIENT	=	$(SRC_CLIENT:.cpp=.o)

NAME_S		=	serv

NAME_C      =   clie

LIBS		=	-lpthread -lcrypto -lssl -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -W -Wall -Wextra

all	:	$(NAME_S) $(NAME_C)

$(NAME_S):	$(OBJ_SERV)
		$(CC) $(OBJ_SERV) $(LIBS) -o $(NAME_S)

$(NAME_C):	$(OBJ_CLIENT)
		$(CC) $(OBJ_CLIENT) $(LIBS) -o $(NAME_C)

clean	:
		$(RM) $(OBJ_SERV) $(OBJ_CLIE)

fclean	:	clean
		$(RM) $(NAME_S) $(NAME_C)

re	:	fclean all
