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
				Monsters/Meteora.cpp      \
				GameEngine/RTypeServer.cpp	   \
				Monsters/Nautilus.cpp       \
                                                     Monsters/Robot.cpp

OBJ_GAME	=		$(SRC_GAME:.cpp=.o)

SRC_GAME_CL	=	main_client.cpp			\
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
				GameEngine/RTypeServer.cpp  \
				Monsters/Meteora.cpp        \
				Monsters/Nautilus.cpp       \
                                                     Monsters/Robot.cpp

OBJ_GAME_CL	=		$(SRC_GAME_CL:.cpp=.o)

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
				Monsters/Meteora.cpp        \
                Monsters/Nautilus.cpp       \
                                                     Monsters/Robot.cpp

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
				clie_test.cpp               \
				Monsters/Meteora.cpp        \
                Monsters/Nautilus.cpp       \
                Monsters/Robot.cpp

OBJ_CLIENT	=	$(SRC_CLIENT:.cpp=.o)

CXXFLAGS    =   -g3

NAME_S		=	serv

NAME_C      	=   ../SFML/clie

NAME_G		= 	game

NAME_G_C    =   game_cl

LIBS		=	-lpthread -lcrypto -lssl -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -W -Wall -Wextra

all	:	$(NAME_S) $(NAME_C) $(NAME_G) $(NAME_G_C)

$(NAME_S):	$(OBJ_SERV)
		$(CC) $(OBJ_SERV) $(LIBS) -o $(NAME_S)

$(NAME_C):	$(OBJ_CLIENT)
		$(CC) $(OBJ_CLIENT) $(LIBS) -o $(NAME_C)

$(NAME_G):	$(OBJ_GAME)
		$(CC) $(OBJ_GAME) $(LIBS) -o $(NAME_G)

$(NAME_G_C):	$(OBJ_GAME_CL)
		$(CC) $(OBJ_GAME_CL) $(LIBS) -o $(NAME_G_C)

clean	:
		$(RM) $(OBJ_SERV) $(OBJ_CLIENT) $(OBJ_GAME) $(OBJ_GAME_CL)

fclean	:	clean
		$(RM) $(NAME_S) $(NAME_C) $(NAME_G) $(NAME_G_C)

re	:	fclean all
