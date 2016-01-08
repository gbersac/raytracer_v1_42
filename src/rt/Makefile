################################################################################
# BASIC VARIABLES															   #
################################################################################

SRCS				:= main.c load_file.c render.c parse.c parse2.c \
  					sphere.c cam.c light.c image.c handle.c free.c vector1.c \
					vector2.c render2.c plan.c rotate_cam.c ray.c cone.c \
					cylinder.c primitives.c cylinder_inter.c

PATH_OBJ			:= obj
PATH_SRC			:= src
PATH_INC			:= inc

CFLAGS				:= -Wall -Wextra -Werror
OBJECTS				:= $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRCS))
OBJECTS_TEST		:= $(patsubst %.c, $(PATH_OBJT)/%, $(SRCS_TEST))

TEST_CMD			:= $(patsubst %.c, $(PATH_OBJT)/%;, $(SRCS_TEST))

################################################################################
# LIBRARY VARIABLES															   #
################################################################################

export DIR_LIBFT	:= ../libft
export DIR_LIBMATH	:= ../libmath

LIB_MATH			:= -L$(DIR_LIBMATH) -lmath
LIB_FT				:= -L$(DIR_LIBFT) -lft
MLX					:= -L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL -framework AppKit

export DIR_LIB 		:= $(DIR_LIBFT) $(DIR_LIBMATH)

LIBRARY				:= $(LIB_FT) $(LIB_MATH) $(MLX)
INCLUDES			:= -I./$(PATH_INC) $(patsubst %,-I%/inc,$(DIR_LIB))

################################################################################
# BASIC RULES																   #
################################################################################

.PHONY: all test

all: $(APP)

$(APP): $(OBJECTS)
	cc -o $@ $(OBJECTS) $(LIBRARY) $(DEBUG)

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.c)
	@mkdir -p $(PATH_OBJ)
	cc -c -o $@ $(CFLAGS) $^ $(DEBUG) $(INCLUDES)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(APP)

re: fclean $(APP)
