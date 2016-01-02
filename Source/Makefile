CC	=	g++
RM	=	rm -f

SRC_GAME	=		main.cpp			\
				System/Animation.cpp		\
				System/RTypeException.cpp	\
				System/ResourcesBank.cpp	\
				System/window.cpp		\
				GameEngine/Laser.cpp		\
				GameEngine/LinuxSocket.cpp	\
				GameEngine/GameData.cpp		\
				GameEngine/Monster.cpp		\
				GameEngine/Level.cpp		\
				GameEngine/OnLevel.cpp		\
				GameEngine/MutexVault.cpp	\
				Monsters/BasicShip.cpp		\
				GameEngine/ISocket.cpp		\
				GameEngine/Packet.cpp		\
				GameEngine/Rsa.cpp		\
				GameEngine/BBException.cpp	\
				GameEngine/Geometry.cpp         \
				GameEngine/Object.cpp           \
				GameEngine/Artifices.cpp	\
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

OBJ_GAME	=		$(SRC_GAME:.cpp=.o)

SRC_SERV	=		serv_test.cpp			\
				System/Animation.cpp		\
				System/RTypeException.cpp	\
				System/ResourcesBank.cpp	\
				System/window.cpp		\
				GameEngine/LinuxSocket.cpp	\
				GameEngine/GameData.cpp		\
				GameEngine/Level.cpp		\
				GameEngine/OnLevel.cpp		\
				GameEngine/Monster.cpp		\
				Monsters/BasicShip.cpp		\
				GameEngine/MutexVault.cpp	\
				GameEngine/ISocket.cpp		\
				GameEngine/Packet.cpp		\
				GameEngine/Rsa.cpp		\
				GameEngine/BBException.cpp	\
				GameEngine/Geometry.cpp         \
				GameEngine/Object.cpp           \
				GameEngine/Laser.cpp		\
				GameEngine/Artifices.cpp	\
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

SRC_CLIENT	=		System/Animation.cpp		\
				System/RTypeException.cpp	\
				System/ResourcesBank.cpp	\
				System/window.cpp		\
				GameEngine/LinuxSocket.cpp	\
				GameEngine/GameData.cpp		\
				GameEngine/Level.cpp		\
				GameEngine/Monster.cpp		\
				Monsters/BasicShip.cpp		\
				GameEngine/OnLevel.cpp		\
				GameEngine/MutexVault.cpp	\
				GameEngine/ISocket.cpp		\
				GameEngine/Packet.cpp		\
				GameEngine/Rsa.cpp		\
				GameEngine/BBException.cpp	\
				GameEngine/Geometry.cpp         \
				GameEngine/Object.cpp           \
				GameEngine/Laser.cpp		\
				GameEngine/Artifices.cpp	\
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
				GameEngine/RTypeServer.cpp	\
				clie_test.cpp

OBJ_CLIENT	=	$(SRC_CLIENT:.cpp=.o)

NAME_S		=	serv

NAME_C      	=   ../SFML/clie

NAME_G		= 	game

LIBS		=	-lpthread -lcrypto -lssl -g3 -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -W -Wall -Wextra

all	:	$(NAME_S) $(NAME_C) $(NAME_G)

$(NAME_S):	$(OBJ_SERV)
		$(CC) $(OBJ_SERV) $(LIBS) -o $(NAME_S)

$(NAME_C):	$(OBJ_CLIENT)
		$(CC) $(OBJ_CLIENT) $(LIBS) -o $(NAME_C)

$(NAME_G):	$(OBJ_GAME)
		$(CC) $(OBJ_GAME) $(LIBS) -o $(NAME_G)

clean	:
		$(RM) $(OBJ_SERV) $(OBJ_CLIE) $(OBJ_GAME)

fclean	:	clean
		$(RM) $(NAME_S) $(NAME_C) $(OBJ_GAME)

re	:	fclean all
