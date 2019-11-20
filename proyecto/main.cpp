#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
using namespace std;
int fun(int x,string player);
int main(){
    int x;
    string player;
    bool flag=true;
    cout<<"Nombre del jugador\n";
        cin>>player;
    ofstream name;
    name.open("jugadores",ios::app);//abro un archivo y digito la ultima linea//
    name<<player<<endl;//ingreso la variable player en el archivo//
    name.close();//cierro el archivo//
    while(flag==true){//un bucle para que se repita el menu//
        cout<<"\t\tElija una opcion\n1-nivel 1\n2-nivel 2\n3-nivel 3\n4-nivel 4\n5-cerrar\n";
        cin>>x;
        switch(x){//en cada caso muestro la funcion fun con su respectivo archivo de laberinto//
            case 1:
                fun(x,player);
                break;
            case 2:
                fun(x,player);
                break;
            case 3:
                fun(x,player);
                break;
            case 4:
                fun(x,player);
                break;
            case 5:
                flag=false;
                break;
                }
        }
    return 0;
}

int fun(int x,string player){
    ifstream archivo;
    switch(x){ //un switch para elegir que archivo abrir
        case 1:
            archivo.open("lab1");
            break;
        case 2:
            archivo.open("lab2");
            break;
        case 3:
            archivo.open("lab3");
            break;
        case 4:
            archivo.open("lab4");
            break;
    }
    char matriz[16][16];//creo la matriz en donde llenare el laberinto con 0 y 1//
    string line;//creo la variable linea que seran mi lineas en el archivo//
    int numCol = 0;
    int numFila = -1;
    while(!archivo.eof()){ // mientras el archivo no se cierre//
        getline(archivo,line);//leo el archivo linea por linea//
        numFila += 1 ;
        numCol = line.length(); //la catindad de columnas sera igual al tamano de la linea//
        for(int i = 0;i<numCol;i++){ //lleno la matriz con la variable line//
            matriz[i][numFila]=line[i];
        }
    }
    archivo.close();//cierro archivo//
    //creo diversos textures y sprites//
    sf::Texture coin;
    sf::Texture suelo;
    sf::Sprite coin1;
    sf::Sprite pantalla[16][16];//la matriz que sera la encargada de llenar con imagens la pantalla//
    sf::Texture bola;
    sf::Sprite bola1;
    if (!coin.loadFromFile("/home/fundamentos/Documentos/coin.png")){//mando a llamar de donde viene la textura coin//
    }
    if (!bola.loadFromFile("/home/fundamentos/Documentos/punto.png")){//mando a llamar de donde viene la textura bola//
    }
    //textura para el fondo
    if (!suelo.loadFromFile("/home/fundamentos/Imágenes/suelo1.png")){
    }
    //muestro a sans en pantalla
        bola1.setTexture(bola);
        bola1.setPosition(0,165.5);

     string movimiento;//creo una variable para definir el movimiento//
    //creo la ventana
     sf::RenderWindow window(sf::VideoMode(512, 512), "LABERINTO");
    while (window.isOpen())
    {
        sf::Event event;
        //reproduzo el fondo en toda la pantalla
         for(int i = 0;i<16;i++){
            for(int j = 0;j<16;j++){
                pantalla[i][j] = sf::Sprite(suelo);//lleno la matriz con las imagens de suelo//
                if(matriz[i][j] == '0') pantalla[i][j].setTextureRect(sf::IntRect(128,128,32,32));
                if(matriz[i][j] == '1') pantalla[i][j].setTextureRect(sf::IntRect(0,0,32,32));
                if(matriz[i][j] == 's') pantalla[i][j]=sf::Sprite(coin);
                pantalla[i][j].setPosition(i*32,j*32);//posiciono los puntos de la matriz de 32*32 cuadros//
            }
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();}

        }
        //creo el comando de colicion para la pantalla[i][j]//
         for(int i = 0;i<16;i++){
            for(int j = 0;j<16;j++){
                if(bola1.getGlobalBounds().intersects(pantalla[i][j].getGlobalBounds())&&matriz[i][j]=='0') {//si es 0 no se puede mover//
                        if(movimiento == "arriba") bola1.move(0,0.5f);
                        if(movimiento=="abajo") bola1.move(0,-0.5f);
                        if(movimiento=="izquierda")bola1.move(0.5f,0);
                        if(movimiento=="derecha")bola1.move(-0.5f,0);
                }
                if(bola1.getGlobalBounds().intersects(pantalla[i][j].getGlobalBounds())&&matriz[i][j]=='s'){//si es s se caba el juego//
                        cout<<"\t\tFELICIDADES "<<player<<endl;
                       return 0;
                }
            }
        }
        //ingreso comandos para movimiento
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            movimiento = "arriba";
            bola1.move(0,-0.5f);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            movimiento = "abajo";
            bola1.move(0,0.5f);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            movimiento = "izquierda";
            bola1.move(-0.5f,0);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            movimiento = "derecha";
            bola1.move(0.5f,0);
        }

        //limpio la pantalla//
        window.clear();

        // dibujo los sprite
        for(int i = 0;i<16;i++){
            for(int j = 0;j<16;j++){
                window.draw(pantalla[i][j]);
            }
        }
        window.draw(bola1);

        // muestro la pantalla
        window.display();
    }
    return 0;

}


