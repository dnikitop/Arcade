
class pacman
{
public:
    double x;
    double y;
    int i;
    int j;
    void drawleft(void);
    void drawright(void);
    void drawup(void);
    void drawdown(void);
    void drawvoid(void);

};
class coins
{
public:
    int state,x,y;
    void draw(void);
    void SetCoins(int x0, int y0);
};
class ghost
{
public:
    double x;
    double y;
    int i;
    int j;
    void draw(int red,int green, int blue);
    void findPacman(pacman pac);
    ghost(double initx, double inity);
};

class CharBitmap
{
protected:
    int wid,hei;
    char *dat;
    coins *coin;
    pacman pac;
    ghost redGH;
    ghost pinkGH;
    ghost orangeGH;
    ghost tealGH;
    
public:
    CharBitmap();
    ~CharBitmap();
    void CleanUp(void);
    
    // Add copy constructor and copy-assignment operator
    
    void SetBitmap(int bmpWid,int bmpHei,char bmp[]);
    void SetPixel(int x,int y,char c);
    
    void Print(void);
    void Draw(int key);
    char GetPixel(int x,int y);
    
    CharBitmap &operator=(const CharBitmap &incoming);
    void Set(const char *incoming,const int width,const int height);
    const int width(void) const;
    const int height(void) const;
    const char *data(void) const;
    CharBitmap(const CharBitmap &incoming);
    int move(int retval, int key);
    int play();
    int dir(int i,int j, int itar, int jtar);
    int pinkghostInit();
    int tealghostInit();
    int orangeghostInit();
    int findnum();

};
