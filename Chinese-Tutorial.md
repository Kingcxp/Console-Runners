## 我是怎么做出ConsoleRunners的
#### By Kingcq

### 前置知识
#### 字符集编码方式
&emsp;&emsp;在 C/C++ 语言标准中定义了其运行时的字符集环境为 "C" ，也就是 ASCII 字符集的一个子集。而这个字符集通常并不能完整地表示我们平时需要用到的一些字符，比如我们游戏中小人的头'○'就会被显示成'?'  
&emsp;&emsp;那怎么解决这个问题呢？C 语言标准库<locale.h>当中为我们准备了`setlocale`这个方法来帮助我们调整程序的本地化设置。  
&emsp;&emsp;在我写的这个游戏中，我们始终使用 en_US.UTF-8 字符集来编写，大部分常用的命令行环境都是支持的，至少到目前为止，除了一些字符仍然无法正常显示以外，我还没有遇到任何的与环境有关系的问题。（了解下来问题其实可能还蛮大的，但是以我周围大部分人的环境不会有任何的问题）  
&emsp;&emsp;设置起来非常方便，只需要一行就好。  
```c
setlocale(LC_ALL, "en_US.UTF-8");
```

#### 输入和输出控制，掌控命令行的每个字符
&emsp;&emsp;读取键盘键入这个事应该很多人都知道，Windows 下有一个 C 库叫<conio.h>，它里面的方法（`kbhit`）能够很轻易地判断出当前有没有键入，以及读入一个键盘输入（`getch`）。这个操作在 Windows 环境下很容易做到，但是在 Unix 命令行环境当中，情况有所不同，这个库并不是 C 的标准库，除了 Windows 其它平台并没有，这怎么办呢？  
&emsp;&emsp;实际上通过搜索就能够找到很多的解决方案，但是有不少实际执行起来有点问题，不符合实际需要，我在这里就把经过我挑出来的方案放出来。  
```c
#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
    #include <unistd.h>

    static struct termios initial_settings, new_settings;
    static int peek_character = -1;
#endif
// 判断是否有键入
int keyboardHit() {
    #ifdef _WIN32
        return kbhit();
    #else
        char ch;
        int nread;
        if(peek_character != -1) {
            return 1;
        }
        new_settings.c_cc[VMIN] = 0;
        tcsetattr(0, TCSANOW, &new_settings);
        nread = read(0, &ch, 1);
        new_settings.c_cc[VMIN] = 1;
        tcsetattr(0, TCSANOW, &new_settings);
        if(nread == 1) {
            peek_character = ch;
            return 1;
        }
        return 0;
    #endif
}
// 读取单个键入字符
int termGetch() {
    #ifdef _WIN32
        return getch();
    #else
        char ch;
        if(peek_character != -1) {
            ch = peek_character;
            peek_character = -1;
            return ch;
        }
        read(0, &ch, 1);
        return ch;
    #endif
}
// 初始化终端环境，\033字符的事情之后再说
void initConsole() {
    #ifndef _WIN32
        // init keyboard
        tcgetattr(0, &initial_settings);
        new_settings = initial_settings;
        new_settings.c_lflag &= ~ICANON;
        new_settings.c_lflag &= ~ECHO;
        new_settings.c_lflag &= ~ISIG;
        new_settings.c_cc[VMIN] = 1;
        new_settings.c_cc[VTIME] = 0;
        tcsetattr(0, TCSANOW, &new_settings);
    #endif
    setlocale(LC_ALL, "en_US.UTF-8");
    wprintf(L"\033[?25l\033[1;1H\033[2J");
}
// 结束终端环境
void endConsole() {
    #ifndef _WIN32
        // close keyboard
        tcsetattr(0, TCSANOW, &initial_settings);
    #endif
    wprintf(L"\033[?25h\033[1;1H\033[2J");
}
```

#### \033 ANSI 屏幕控制码
&emsp;&emsp;在终端中，ANSI定义了用于屏幕显示的Escape屏幕控制码，在printf函数调用时可以输出具有颜色的字符，这个特性对于绝大部分终端都是有效的，因此我们借助这个方法能够实现很多东西。  
&emsp;&emsp;比如上面的`\033[?25l`和`\033[?25h`就分别代表隐藏和显示光标，`\033[y;xH`代表将光标移动到第y行第x列处（从1开始），`\033[2J`表示清屏。  
&emsp;&emsp;借助`\033`我们能够定义一些基础的实用小方法：  
```c
// 设置光标位置（我的光标位置是从0开始算的，所以要加一）
void setCursor(const int x, const int y) {
    wprintf(L"\033[%d;%dH", y + 1, x + 1);
}
// 大部分终端都支持的颜色（注意！部分颜色在不同终端中表现不相同）
typedef enum Color {
    Color_Escape,
    Color_Black,
    Color_DarkGray,
    Color_BlackUnderline,
    Color_BlackBlink,
    Color_Blue,
    Color_LightBlue,
    Color_BlueUnderline,
    Color_BlueBlink,
    Color_Green,
    Color_LightGreen,
    Color_GreenUnderline,
    Color_GreenBlink,
    Color_Cyan,
    Color_LightCyan,
    Color_CyanUnderline,
    Color_CyanBlink,
    Color_Red,
    Color_LightRed,
    Color_RedUnderline,
    Color_RedBlink,
    Color_Purple,
    Color_LightPurple,
    Color_PurpleUnderline,
    Color_PurpleBlink,
    Color_Brown,
    Color_Yellow,
    Color_YellowUnderline,
    Color_YellowBlink,
    Color_LightGray,
    Color_White,
    Color_GrayUnderline,
    Color_GrayBlink,
} Color;
const wchar_t *ANSI_Colors[] = {
    L"\033[0m",
    L"\033[0;30m",
    L"\033[1;30m",
    L"\033[4;30m",
    L"\033[5;30m",
    L"\033[0;34m",
    L"\033[1;34m",
    L"\033[4;34m",
    L"\033[5;34m",
    L"\033[0;32m",
    L"\033[1;32m",
    L"\033[4;32m",
    L"\033[5;32m",
    L"\033[0;36m",
    L"\033[1;36m",
    L"\033[4;36m",
    L"\033[5;36m",
    L"\033[0;31m",
    L"\033[1;31m",
    L"\033[4;31m",
    L"\033[5;31m",
    L"\033[0;35m",
    L"\033[1;35m",
    L"\033[4;35m",
    L"\033[5;35m",
    L"\033[0;33m",
    L"\033[1;33m",
    L"\033[4;33m",
    L"\033[5;33m",
    L"\033[0;37m",
    L"\033[1;37m",
    L"\033[4;37m",
    L"\033[5;37m",
};
```

有了这些前置知识，编写游戏的所有工具就齐了，接下来就是代码框架和游戏结构的设计。

### 卑微的开始

&emsp;&emsp;基本的游戏逻辑，无论是图形界面还是纯文本界面，我觉得实际上都是几乎完全一致的，游戏的一次刷新作为一帧，计算出这一帧过去的时间和发生的所有事件，并借助这些数据进行处理，随后处理输出图像。只不过纯文本的事件处理更加简单，仅仅包含键盘按键的读入作为事件。  

&emsp;&emsp;所以我们凭借着这样的理解和上面准备好的小工具，很容易能写出主函数当中的内容（事件处理、更新、绘制在之后会提到，在这里略过）：  
```c
int main(int argc, char *argv[]) {
    initConsole();

    bool loop = true;
    clock_t now = clock();

    while (loop) {
        int ch = 0;
        while (keyboardHit()) {
            ch = termGetch();
            // 在这里根据 ch 处理事件
        }
        // 计算过去的时间
        float deltaTime = (float)(clock() - now) / (float)CLOCKS_PER_SEC;
        now = clock();
        // 根据事件更新游戏状态

        // 在这里绘制游戏画面
    }

    endConsole();
    return EXIT_SUCCESS;
}
```

### C 语言的面向对象
&emsp;&emsp;一个相对复杂的游戏的帧逻辑过程一定也是复杂的，你真的想把所有的东西全部都塞在 `main.c` 这一个文件里面吗？那一定非常的难看吧！这对于代码的编写和修改都是极为致命的——你的脑袋根本装不下这么多的代码！  
&emsp;&emsp;那你紧接着肯定就会想到，我把这些代码按照含义分开成多个文件，然后再 include 进来，这不就好了吗？这种做法的确非常有效，但是仍然非常的耗脑子，对于某一个“物体”，比如一个按钮，或者一个人物，有很多个变量都和他们相关，你可能需要在多个文件里同时追踪这许多变量，这可太难做到了！  
&emsp;&emsp;那么，有没有更好的办法，能够让我们能够专注于“物体”本身，将它的属性全部收纳到一起，将追踪“属性”转变为更简单的追踪“物体”呢？  
&emsp;&emsp;这就是面向对象的思路——对数据进行“降维打击”，从更高的层面去专注于“物体”本身，而不是它的每一个“属性”。  
&emsp;&emsp;要说把很多种数据组合在一起，那么 C 语言当中我们只有可能想到一种类型：struct 结构体。那我们可以写出类似于这样的代码：  
```c
// 记录一个盒子的长宽高和重量
typedef struct Box {
    int h, w, d, weight;
} Box;
// 一个人，手中可能抱了盒子，最大能抓住多重的盒子
typedef struct Person {
    int bearing;
    Box *boxInHand;
} Person;
```
&emsp;&emsp;这个时候，我们如果想让一个`Person`抱起一个`Box`，我们需要这样写：  
```c
if (person.bearing >= box.weight && person.boxInHand == NULL) {
    person.boxInHand = &box;
}
```
&emsp;&emsp;这实际上还是略显复杂了，想象现在有一个非常复杂的“搬运”过程，你要用这种形式在各处需要“搬运”的地方都写上吗？还是老问题，我们没有专注于“物体”本身，而是仍然将“物体”拆分为单个数据在处理。  
&emsp;&emsp;实际上我们更想要写出这样的代码：  
```c
person.carry(&box);
```
&emsp;&emsp;但是 C 语言并不允许我们在结构体里面塞函数，只能塞变量和指针，这怎么办才好呢？  
&emsp;&emsp;实际上答案已经呼之欲出了，那就是使用函数指针，并且我们在创建`Person`实例的时候需要将对应的函数赋给它，这意味着我们需要重新自定义`Person`物体的创建过程，从这样的做法为之后的编程带来的便利来看，这一点牺牲实际上是非常赚的：  
```c
typedef struct Person {
    void (*carry)(struct Person *p, Box *box);
    int bearing;
    Box *boxInHand;
} Person;

void Person_carry(Person *p, Box *box) {
    if (p->bearing >= box->weight && p->boxInHand == NULL) {
        p->boxInHand = &box;
    }
}

Person *createPerson() {
    Person *p = (Person *)malloc(sizeof(Person));
    p->carry = Person_carry;
    return p;
}

void destroyPerson(Person *p) {
    free(p);
}
```
&emsp;&emsp;我们通常把一个类分成一个文件存储，在这里我们可以将这个类存为`Person.h`，并为它两边加上这样的定义以避免多次定义：  
```c
// 如果没有定义过 Person
#ifndef PERSON
// 定义 Person 并做接下来的事
#define PERSON
// 上面的代码写在这里
#endif // 结束上面的 ifndef 条件语句
```

### 坏了！它们俩怎么互相需要啊？
&emsp;&emsp;人能把盒子抱起来，有的时候，盒子也能装人。  
&emsp;&emsp;在这种情境下，`Person.h`需要 #include "`Box.h`"，而`Box.h`需要 #include "`Person.h`"。  
&emsp;&emsp;这坏了！`Person.h`需要`Box.h`，`Box.h`里包含`Person.h`就又会把`Person.h`拿过来……如此递归调用，虽然我们之前的操作能够避免重复定义，但是这两个文件最后总得分个先后，总有一个会拿不到另一个的定义。  
&emsp;&emsp;这可怎么办呢？我们可以先声明，再调用。我们发现`Person.h`里并不需要 `Box` 真实存在，我们只需要知道有这么个东西就行，那我们可以只声明有 `Box` 这个东西，但是不说它到底是什么，等到之后再说。  
&emsp;&emsp;所以，取消`Person.h`包含`Box.h`的行为，而替换为`typedef struct Box Box;`，代码仍然可以正常运行。  
&emsp;&emsp;等等，真的能正常运行吗？如果你真的去试了，你就会发现并不行。  
&emsp;&emsp;仔细看，在 `carry` 方法中，我们用到了 `Box` 的属性，而此时 `Box` 还没有给出定义，仅仅只是一个不完整的指针，C 语言不知道这个属性到哪里去找，所以这样仍然没有办法编译成功。  
&emsp;&emsp;那难道就没有别的办法了吗？当然有！我们将定义和实现拆开，`Person.h` 当中只留下定义，也就是这样：  
```c
// Person.h
#ifndef PERSON
#define PERSON
typedef struct Person {
    void (*carry)(struct Person *p, Box *box);
    int bearing;
    Box *boxInHand;
} Person;

Person *createPerson();
void destroyPerson(Person *p);
#endif // PERSON
```
&emsp;&emsp;剩下的实现，我们挪到新文件 `Person.c` 里面：  
```c
// Person.c
#include "Person.h"
#include "Box.h"

void Person_carry(Person *this, Box *box) {
    // ...
}
Person *createPerson() {
    // ...
}
void destroyPerson(Person *p) {
    // ...
}
```
&emsp;&emsp;看到了吗？我们可以在实现的时候，需要用到 `Box` 了，再给出 `Box` 的具体定义，实现可以放到所有代码的最后再给出，这个时候，该定义的都定义好了，就不会出现递归包含的问题了。  
&emsp;&emsp;实现只应该也只能被包含一次，而定义可以被包含多次（同时为了代码补全和解决递归包含），这种基本的面向对象结构将会贯穿我们的整个项目，请务必记好。  

### 全局上下文和实用定义
&emsp;&emsp;在定下整个项目的基调之后，我们需要一些具体的东西来帮助我们管理一些必须要在全局都有定义的实例和方法。我在这个项目中引入了 `Globals.h` ，其中的 `Globals` 结构体塞入了所有全局实例的指针（如画布、计分板等），并将需要用到的常用函数也放在了这个文件里，例如生成伪随机数的 `random` 方法以及之前提到的终端操作方法。  
&emsp;&emsp;除了全局上下文之外，我们还需要一些实用的定义，比如说将点坐标包装成一个二维的向量，用左上角坐标和宽高描述矩形等，并且我加入了用来判断矩形是否碰撞和包含某个坐标的方法，这个在之后的游戏过程的编写中时常需要用到：  
```c
typedef struct Vector2i {
    int x, y;
} Vector2i;

typedef struct Vector2f {
    float x, y;
} Vector2f;

typedef struct Rect {
    int x, y, w, h;
} Rect;

typedef struct FloatRect {
    float x, y, w, h;
} FloatRect;

bool Rect_intersects(const Rect *lhs, const Rect *rhs) {
    return !(lhs->x + lhs->w - 1 < rhs->x || rhs->x + rhs->w - 1 < lhs->x || lhs->y + lhs->h - 1 < rhs->y || rhs->y + rhs->h - 1 < lhs->y);
}

bool Rect_contains(const Rect *rect, const Vector2i *point) {
    return !(point->x < rect->x || rect->x + rect->w - 1 < point->x || point->y < rect->y || rect->y + rect->h - 1 < point->y);
}

bool FloatRect_intersects(const FloatRect *lhs, const FloatRect *rhs) {
    return !(lhs->x + lhs->w < rhs->x || rhs->x + rhs->w < lhs->x || lhs->y + lhs->h < rhs->y || rhs->y + rhs->h < lhs->y);
}

bool FloatRect_contains(const FloatRect *rect, const Vector2f *point) {
    return !(point->x < rect->x || rect->x + rect->w < point->x || point->y < rect->y || rect->y + rect->h < point->y);
}
```

### 终端画布
（在整个制作过程中我都假定终端的大小是足够的，实际上仅对于这个小游戏而言，大部分的情况下都是足够显示的。）  
&emsp;&emsp;知道具体怎么在终端上写字之后，我们还需要一个更加具体的管理方法来帮助我们更便捷高效地绘制终端上的画面。  
&emsp;&emsp;我们引入 `Renderer` 类，它包含一系列方法和画布存储，用来实现对画布的绘制和管理：  
```c
// Renderer.h
typedef struct Renderer {
    // Methods

    void            (*renderCharAt)(const struct Renderer *this, const wchar_t ch, const Color *color, const Vector2i *position);
    void            (*renderStringAt)(const struct Renderer *this, const wchar_t *str, const Color *colors, const Vector2i *position, const bool pure);
    void            (*clear)(const struct Renderer *this);
    void            (*display)(const struct Renderer *this);

    // Variables

    wchar_t         **canvas,
                    **lastCanvas;

    Color           **colors,
                    **lastColors;

    int             width,
                    height,
                    x, y;
} Renderer;

Renderer *createRenderer(int x, int y, int w, int h);
void destroyRenderer(Renderer *renderer);
```
```c
// Renderer.c
#include "Renderer.h"

void setCursor(const int x, const int y) {
    wprintf(L"\033[%d;%dH", y + 1, x + 1);
}

void Renderer_renderCharAt(const Renderer *this, const wchar_t ch, const Color *color, const Vector2i *position) {
    if ((ch == L' ' && (color == NULL || *color == Color_Escape)) || outOfBounds(this, position->x, position->y)) {
        return;
    }
    this->canvas[position->y][position->x] = ch;
    this->colors[position->y][position->x] = color ? *color : Color_Escape;
}

void Renderer_renderStringAt(const Renderer *this, const wchar_t *str, const Color *colors, const Vector2i *position, const bool pure) {
    int len = wcslen(str);
    for (int i = 0; i < len; ++i) {
        if (outOfBounds(this, position->x + i, position->y)) {
            continue;
        }
        Color color;
        if (pure) {
            color = colors ? *colors : Color_Escape;
        } else {
            color = colors ? colors[i] : Color_Escape;
        }
        if (str[i] == L' ' && color == Color_Escape) {
            continue;
        }
        this->canvas[position->y][position->x + i] = str[i];
        this->colors[position->y][position->x + i] = color;
    }
}

void Renderer_clear(const Renderer *this) {
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            this->canvas[i][j] = L' ';
            this->colors[i][j] = Color_Escape;
        }
    }
}

void Renderer_display(const Renderer *this) {
    Color current = Color_Escape;
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            if (this->canvas[i][j] == this->lastCanvas[i][j] && this->colors[i][j] == this->lastColors[i][j]) {
                continue;
            }
            this->lastCanvas[i][j] = this->canvas[i][j];
            this->lastColors[i][j] = this->colors[i][j];
            setCursor(this->x + j, this->y + i);
            if (this->colors[i][j] != current) {
                current = this->colors[i][j];
                wprintf(ANSI_Colors[Color_Escape]);
                wprintf(ANSI_Colors[this->colors[i][j]]);
            }
            putwchar(this->canvas[i][j]);
        }
    }
    wprintf(ANSI_Colors[Color_Escape]);
}

Renderer *createRenderer(int x, int y, int w, int h) {
    Renderer *renderer = (Renderer *)malloc(sizeof(Renderer));
    renderer->width = w, renderer->height = h;
    renderer->x = x, renderer->y = y;
    renderer->canvas = (wchar_t **)malloc(sizeof(wchar_t *) * renderer->height);
    renderer->lastCanvas = (wchar_t **)malloc(sizeof(wchar_t *) * renderer->height);
    renderer->colors = (Color **)malloc(sizeof(Color *) * renderer->height);
    renderer->lastColors = (Color **)malloc(sizeof(Color *) * renderer->height);
    for (int i = 0; i < renderer->height; ++i) {
        renderer->canvas[i] = (wchar_t *)malloc(sizeof(wchar_t) * renderer->width);
        renderer->lastCanvas[i] = (wchar_t *)malloc(sizeof(wchar_t) * renderer->width);
        renderer->colors[i] = (Color *)malloc(sizeof(Color) * renderer->width);
        renderer->lastColors[i] = (Color *)malloc(sizeof(Color) * renderer->width);
        for (int j = 0; j < renderer->width; ++j) {
            renderer->canvas[i][j] = L' ';
            renderer->lastCanvas[i][j] = L' ';
            renderer->colors[i][j] = Color_Escape;
            renderer->lastColors[i][j] = Color_Escape;
        }
    }
    renderer->renderCharAt = Renderer_renderCharAt;
    renderer->renderStringAt = Renderer_renderStringAt;
    renderer->clear = Renderer_clear;
    renderer->display = Renderer_display;

    return renderer;
}

void destroyRenderer(Renderer *renderer) {
    for (int i = 0; i < renderer->height; ++i) {
        free(renderer->canvas[i]);
        free(renderer->lastCanvas[i]);
        free(renderer->colors[i]);
        free(renderer->lastColors[i]);
    }
    free(renderer->canvas);
    free(renderer->lastCanvas);
    free(renderer->colors);
    free(renderer->lastColors);

    free(renderer);
}

```
#### 为什么要写成这样？
&emsp;&emsp;虽然听上去不应该，但实际上在终端上绘制字符是要比绘制图像画面更加慢的，如果每一个游戏帧将整个屏幕清空再重新绘制，会严重地拖慢游戏速度，甚至会导致极为严重的操作延迟、闪屏等问题，十分影响游戏体验。同时考虑到字符界面的特殊性，我们有时并不需要完全将整个画面擦除，我们可以通过比较当前帧和上一帧画面的区别，只将发生变化的区域进行重绘，这样就能极大程度地减少绘制次数，提高游戏帧率，提升游戏体验。  
&emsp;&emsp;同时，我们也考虑到了透明度的问题，如果绘制的字符是一个 __无色__ 的空格，那我们会将它认为是一个透明的字符，即不占据任何空间，因此它也不会覆盖下面的字符。  
&emsp;&emsp;同样被考虑到的是提供字符颜色的问题，可以看到在方法中每个字符都会与颜色对应，但有的时候我们只需要绘制纯色的字符串，或者我们根本不需要颜色。因此我们将颜色改为传入指针，当指针为空时，颜色为无色。同时当 `renderStringAt` 方法的 `pure` 参数被标记为 `true` 时，我们认为字符串是纯色的，传入的颜色指针不再被视为数组而是单个变量。  
&emsp;&emsp;实际编写的时候，我使用了每绘制一个字符就重新调整一次绘制颜色的策略，但是在 Linux 的终端环境下我遇到了字符绘制不完整的情况，让我难受了整整一个下午。在之后的测试中发现，似乎是 `\033` 控制字符的绘制次数存在一定的限制，同时太多次的绘制会导致绘制失败。因此我重新优化了绘制策略，保存当前绘制的颜色，如果接下来绘制的颜色仍然相同，那么不再重新设置颜色，同时超出画布范围的字符不再绘制，这样能够解决所有的这些问题。  

### 状态栈，轻松管理游戏状态
&emsp;&emsp;直接举例子来看，比方说你进入游戏，首先映入眼帘的是一个开始界面，点击开始游玩按钮，你才会跳转到游戏界面，游戏界面中按下暂停键，你会看到暂停的面板悬停在游戏画面的上方，但这个时候游戏界面可能还在运动，但并不会接收你的操作，返回并退出游戏界面，你会发现你重新回到了开始菜单。  
&emsp;&emsp;如果我们把每一个界面看作一个状态的话，我们是否可以认为这些状态在一个栈上，当栈为空的时候，游戏结束，初始压入主菜单状态，当点击开始游戏，将游戏状态压入，按下暂停再将暂停状态压入，退出时再依次弹出，而每个状态都能决定其下方的状态能否被看到，以及是否更新或者接收事件。  
&emsp;&emsp;这便是状态和状态栈这个想法的由来，我们通过状态栈来管理游戏状态，同时通过状态栈的压入和弹出，来控制游戏状态的切换：
```c
// State.h
#ifndef STATE
#define STATE


#include "../Globals.h"

#define STATE_SLOTS 32

typedef struct StateStack StateStack;

typedef enum StateID {
    GameState,
    PauseState,
    MenuState,
    ReviveState,
    StoreState,
    InfoState,
} StateID;

typedef struct State {
    // Methods

    bool            (*handleEvent)(struct State *this, const int key);
    bool            (*update)(struct State *this, float deltaTime);
    void            (*render)(const struct State *this, const Renderer *renderer);

    // Variables

    StateStack      *stack;
    Globals         *globals;
    bool            isLowerVisible;
    void            *slots[STATE_SLOTS];
} State;

State *createState(Globals *globals, StateStack *stack, StateID id);
void destroyState(State *statek, StateID id);

State *createGameState(Globals *globals, StateStack *stack);
void destroyGameState(State *state);

State *createPauseState(Globals *globals, StateStack *stack);
void destroyPauseState(State *state);

State *createMenuState(Globals *globals, StateStack *stack);
void destroyMenuState(State *state);

State *createReviveState(Globals *globals, StateStack *stack);
void destroyReviveState(State *state);

State *createStoreState(Globals *globals, StateStack *stack);
void destroyStoreState(State *state);

State *createInfoState(Globals *globals, StateStack *stack);
void destroyInfoState(State *state);

#endif // STATE
```
```c
// State.c
#include "State.h"
#include "StateStack.h"

State *createState(Globals *globals, StateStack *stack, StateID id) {
    State *state = NULL;
    switch (id) {
        case GameState:
            state = createGameState(globals, stack);
            break;
        case PauseState:
            state = createPauseState(globals, stack);
            break;
        case MenuState:
            state = createMenuState(globals, stack);
            break;
        case ReviveState:
            state = createReviveState(globals, stack);
            break;
        case StoreState:
            state = createStoreState(globals, stack);
            break;
        case InfoState:
            state = createInfoState(globals, stack);
            break;
        default:
            break;
    }
    return state;
}

void destroyState(State *state, StateID id) {
    switch (id) {
        case GameState:
            destroyGameState(state);
            break;
        case PauseState:
            destroyPauseState(state);
            break;
        case MenuState:
            destroyMenuState(state);
            break;
        case ReviveState:
            destroyReviveState(state);
            break;
        case StoreState:
            destroyStoreState(state);
            break;
        case InfoState:
            destroyInfoState(state);
            break;
        default:
            break;
    }
}
```
```c
// StateStack.h
#ifndef STATESTACK
#define STATESTACK


#include "../Globals.h"
#include "State.h"

#define STACK_MAX_LENGTH 8
#define PENDING_MAX_LENGTH 16

typedef enum StackAction {
    StackPush, StackPop, StackClear
} StackAction;

typedef struct PendingTask {
    StackAction action;
    StateID     stateID;
} PendingTask;

typedef struct StateStack {
    // Methods

    void        (*handleEvent)(struct StateStack *this, const int key);
    void        (*update)(struct StateStack *this, float deltaTime);
    void        (*render)(const struct StateStack *this, const Renderer *renderer);

    void        (*pushState)(struct StateStack *this, StateID id);
    void        (*popState)(struct StateStack *this);
    void        (*clearStates)(struct StateStack *this);

    bool        (*isEmpty)(const struct StateStack *this);

    void        (*applyPendingTasks)(struct StateStack *this);

    // Variables

    Globals     *globals;

    int         stackTop,
                pendingFront,
                pendingBack;

    State       *stack[STACK_MAX_LENGTH];
    StateID     idStack[STACK_MAX_LENGTH];

    PendingTask pendingList[PENDING_MAX_LENGTH];
} StateStack;

StateStack *createStateStack(Globals *globals);
void destroyStateStack(StateStack *stack);

#endif // STATESTACK
```
```c
// StateStack.c
#include "StateStack.h"

void StateStack_handleEvent(StateStack *this, const int key) {
    if (this->isEmpty(this)) {
        return;
    }
    for (int i = this->stackTop; i >= 0; --i) {
        if (!this->stack[i]->handleEvent(this->stack[i], key)) {
            break;
        }
    }
    this->applyPendingTasks(this);
}

void StateStack_update(StateStack *this, float deltaTime) {
    if (this->isEmpty(this)) {
        return;
    }
    for (int i = this->stackTop; i >= 0; --i) {
        if (!this->stack[i]->update(this->stack[i], deltaTime)) {
            break;
        }
    }
    this->applyPendingTasks(this);
}

void StateStack_render(const StateStack *this, const Renderer *renderer) {
    if (this->isEmpty(this)) {
        return;
    }
    int i = this->stackTop;
    while (i > 0 && this->stack[i]->isLowerVisible) {
        --i;
    }
    for (; i <= this->stackTop; ++i) {
        this->stack[i]->render(this->stack[i], renderer);
    }
}

void StateStack_pushState(StateStack *this, StateID id) {
    if (this->stackTop == -1) {
        this->stack[++this->stackTop] = createState(this->globals, this, id);
        this->idStack[this->stackTop] = id;
        return;
    }
    this->pendingBack = (this->pendingBack + 1) % PENDING_MAX_LENGTH;
    this->pendingList[this->pendingBack].action = StackPush;
    this->pendingList[this->pendingBack].stateID = id;
}

void StateStack_popState(StateStack *this) {
    this->pendingBack = (this->pendingBack + 1) % PENDING_MAX_LENGTH;
    this->pendingList[this->pendingBack].action = StackPop;
}

void StateStack_clearStates(StateStack *this) {
    this->pendingBack = (this->pendingBack + 1) % PENDING_MAX_LENGTH;
    this->pendingList[this->pendingBack].action = StackClear;
}

bool StateStack_isEmpty(const StateStack *this) {
    return this->stackTop == -1;
}

void StateStack_applyPendingTasks(StateStack *this) {
    while (this->pendingFront != (this->pendingBack + 1) % PENDING_MAX_LENGTH) {
        switch (this->pendingList[this->pendingFront].action) {
            case StackPush:
                if (this->stackTop + 1 < STACK_MAX_LENGTH) {
                    this->stack[++this->stackTop] = createState(this->globals, this, this->pendingList[this->pendingFront].stateID);
                    this->idStack[this->stackTop] = this->pendingList[this->pendingFront].stateID;
                }
                break;
            case StackPop:
                if (this->stackTop >= 0) {
                    destroyState(this->stack[this->stackTop], this->idStack[this->stackTop]);
                    --this->stackTop;
                }
                break;
            case StackClear:
                while (this->stackTop >= 0) {
                    destroyState(this->stack[this->stackTop], this->idStack[this->stackTop]);
                    --this->stackTop;
                }
                break;
            default:
                break;
        }
        this->pendingFront = (this->pendingFront + 1) % PENDING_MAX_LENGTH;
    }
}

StateStack *createStateStack(Globals *globals) {
    StateStack *stack = (StateStack *)malloc(sizeof(StateStack));

    stack->globals = globals;

    stack->stackTop = -1;
    stack->pendingFront = 0;
    stack->pendingBack = -1;

    stack->handleEvent = StateStack_handleEvent;
    stack->update = StateStack_update;
    stack->render = StateStack_render;
    stack->pushState = StateStack_pushState;
    stack->popState = StateStack_popState;
    stack->clearStates = StateStack_clearStates;
    stack->isEmpty = StateStack_isEmpty;
    stack->applyPendingTasks = StateStack_applyPendingTasks;

    return stack;
}

void destroyStateStack(StateStack *stack) {
    free(stack);
}
```
&emsp;&emsp;可以看到，这两个类是互相需要的，在一个状态中需要能够获取到状态栈并对它进行一些操作，状态栈当中需要管理当前的所有状态。  
&emsp;&emsp;同时注意到，不同的状态可能还会需要额外的存储一些临时的只属于当前状态的变量和类，因此我为每一个状态都分配了一组`void *`指针，有需要的时候，可以在这个指针里分配各种变量，这也算是低配版的一种类继承的效果吧。  

### 再来简单地存个档？
&emsp;&emsp;当你的游戏逐渐复杂，流程逐渐变长，你可能需要将一些东西保存下来，以保证当玩家下次打开游戏的时候，他们所付出的努力还在。  
&emsp;&emsp;对于我的游戏来说，这实际上很简单！只需要记录下获得的金币数，最高分，当前选中的Runner类型，所有Runner的购买情况就可以了：  
&emsp;&emsp;我有一个计分板类，恰好保存了所有这些东西，我们可以把保存和加载的方法加进去：  
```c
typedef struct ScoreBoard {
    // Methods

    void        (*save)(const struct ScoreBoard *this);
    void        (*load)(struct ScoreBoard *this);

    // Variables

    int         coins,
                highScore,
                runnerIndex;
    
    bool        *runnerUnlocked;

    // In-game variables

    // GameState variables

    float       score;
    bool        isInvincible;
    float       invincibleTimer,
                reviveTimer;
    int         lastRevivedTimes,
                revivedTimes;
} ScoreBoard;

ScoreBoard *createScoreBoard();
void destroyScoreBoard(ScoreBoard *scoreBoard);
```
```c
// in ScoreBoard.c
void ScoreBoard_save(const ScoreBoard *this) {
    FILE *outFile = fopen("save.dat", "w");
    fprintf(outFile, "%d %d %d\n", this->coins, this->highScore, this->runnerIndex);
    for (int i = 0; i < Runner_Count; ++i) {
        if (i == Runner_Count - 1) {
            fprintf(outFile, "%d\n", this->runnerUnlocked[i]);
        } else {
            fprintf(outFile, "%d ", this->runnerUnlocked[i]);
        }
    }
    fclose(outFile);
}

void ScoreBoard_load(ScoreBoard *this) {
    FILE *inFile = fopen("save.dat", "r");
    if (inFile == NULL) {
        this->save(this);
        return;
    }
    fscanf(inFile, "%d%d%d", &this->coins, &this->highScore, &this->runnerIndex);
    for (int i = 0; i < Runner_Count; ++i) {
        fscanf(inFile, "%d", &this->runnerUnlocked[i]);
    }
    fclose(inFile);
}
```
&emsp;&emsp;在读取的时候，我们打开一个特定的文件，将数据读取出来，而在保存的时候，我们新建一个同样特定的文件并存入数据。  
&emsp;&emsp;现在唯一剩下的问题就是保存和载入的时机问题。显然，游戏被打开的时候就应该载入，而保存的问题在这里实际上也十分简单。每当游戏失败结束或者暂停以及购买东西的时候，都需要刷新一下存档的信息，也就是保存。在需要的地方直接调用这个方法就完事了。  

### 结束了？
&emsp;&emsp;真的，实际上编写一个小游戏项目只需要知道这些就够了，剩下的就是游戏设计、代码编写、代码编写、代码编写、代码编写、代码编写……  
&emsp;&emsp;如果你觉得还是没有思路，你可以先浏览一下我的代码，看看我的思路和写法，然后再照猫画虎写一个简单的像是扫雷的小游戏熟悉一下，之后按照自己的想法和实现的要求写就好啦！  
&emsp;&emsp;我的代码都在这里，可以自己看！[Github](https://github.com/Kingcxp/Console-Runners/tree/master/src)
