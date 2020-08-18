#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <bits/stdc++.h>
#include <string>

void move(sf::Sprite *psprite,int *sourceX,int *sourceY,int *i,int *move_speed,int increase,int limit1,int limit2)
{
	if(*move_speed>0)
	{
		if(psprite->getPosition().x<760){psprite->move(*move_speed,0);}
	}
	else
	{
		if(psprite->getPosition().x>20){psprite->move(*move_speed,0);}
	}
	if(*i==0)
	*sourceX+=increase;
	if(*i==1)
	*sourceX=*sourceX-increase;
	std::cout<<*sourceX<<std::endl;
	if(*sourceX>limit1)
	{
		*i=1;
		*sourceX+=-increase;
	}
	if(*sourceX<limit2)
	{
		*i=0;
		*sourceX+=increase;
	}
}

void move_attack(sf::Sprite *p1sprite,int *sourceX,int *sourceY,int *move_speed,int increase,int limit,int initial)
{
	if(*move_speed>0)
	{
		if(p1sprite->getPosition().x<760){p1sprite->move(*move_speed,0);}
	}
	else
	{
		if(p1sprite->getPosition().x>25){p1sprite->move(*move_speed,0);}
	}
	*sourceX+=increase;
	if(*sourceX>limit)
	{
		*sourceX=initial;
	}
	std::cout<<*sourceX<<std::endl;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600),"Yuddh 0.1");
	window.setVerticalSyncEnabled(true);
	
	bool flag_p1_attack1=false,flag_p1_attack2=false,flag_p2_attack1=false,jump=false,collision1=false,p1attack=false,p2attack=false,p1win=false,p2win=false;
	int sourceX=248,sourceY=0,i=0,count=0,p1_movespeed,p2_movespeed,radius=5,source2X=521,source2Y=0,k=0,l=0;
	float frameCounter=0,frameSpeed=500,switchFrame=20,j=0,time=0,distance=20,distance2=14;
	sf::Clock clock;
	
	std::vector<std::string>vec2;
	//std::string string2;
	while(k<102)
	{
		k+=2;
		std::string string2= std::to_string(k);
		vec2.push_back(string2);
	}
	k=0;
	
	sf::Text text;
	sf::Font font;
	if(!font.loadFromFile("FiraSans-Book.otf"))
	{
		std::cout<<"Can't load font"<<std::endl;
	}
	text.setFont(font);
	text.setCharacterSize(50);
	sf::String string;
	string="100";
	text.setString(string);
	text.setFillColor(sf::Color::Red);
	
	sf::Text text2;
	sf::Font font2;
	if(!font2.loadFromFile("FiraSans-Book.otf"))
	{
		std::cout<<"Can't load font"<<std::endl;
	}
	text2.setFont(font2);
	text2.setCharacterSize(50);
	sf::String string2;
	string2="100";
	text2.setString(string2);
	text2.setPosition(690,0);
	text2.setFillColor(sf::Color::Red);
	
	sf::Text text3;
	sf::Font font3;
	if(!font3.loadFromFile("FiraSans-Book.otf"))
	{
		std::cout<<"Can't load font"<<std::endl;
	}
	text3.setFont(font3);
	text3.setCharacterSize(50);
	sf::String string3;
	string3="P1 win";
	text3.setString(string3);
	text3.setPosition(340,0);
	text3.setFillColor(sf::Color::Red);
	
	sf::Text text4;
	sf::Font font4;
	if(!font4.loadFromFile("FiraSans-Book.otf"))
	{
		std::cout<<"Can't load font"<<std::endl;
	}
	text4.setFont(font2);
	text4.setCharacterSize(50);
	sf::String string4;
	string4="P2 win";
	text4.setString(string4);
	text4.setPosition(340,0);
	text4.setFillColor(sf::Color::Red);
	//*******************Player 1************************
	sf::Texture p1texture;
	sf::Sprite p1sprite;
	p1texture.loadFromFile("player1.png");
	p1sprite.setTexture(p1texture);
	p1sprite.setPosition(100,360);
	p1sprite.setOrigin(18,0);
	//p1sprite.setScale({ -1, 1 });
	
	sf::Texture brick;
	sf::RectangleShape rectangle1(sf::Vector2f(200, 200));
	sf::RectangleShape rectangle2(sf::Vector2f(200,200));
	sf::RectangleShape rectangle3(sf::Vector2f(200,200));
	sf::RectangleShape rectangle4(sf::Vector2f(200,200));
	rectangle1.setPosition(0,400);
	rectangle2.setPosition(200,400);
	rectangle3.setPosition(400,400);
	rectangle4.setPosition(600,400);
	//rectangle.setTextureRect(sf::IntRect(10, 10, 100, 100));
	brick.loadFromFile("brick.png");
	rectangle1.setTexture(&brick);
	rectangle2.setTexture(&brick);
	rectangle3.setTexture(&brick);
	rectangle4.setTexture(&brick);
	brick.setSmooth(true);
	
	std::vector <sf::CircleShape> vec;
	sf::CircleShape sonic(radius);
	sonic.setFillColor(sf::Color(0, 0, 0,50));
	while(radius<500)
	{
		sonic.setRadius(radius+=5);
		sonic.setOrigin(radius,radius);
		vec.push_back(sonic);
	}
	
	radius=0;	//Now can be used as flag
	
	//*******************Player 2************************
	sf::Texture p2texture;
	p2texture.loadFromFile("player2.png");
	sf::Sprite p2sprite;
	p2sprite.setTexture(p2texture);
	p2sprite.setPosition(500,342);
	p2sprite.setOrigin(20,0);
	
	//*******************Game Loop***********************
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyReleased:
					flag_p1_attack1=false;
					flag_p1_attack2=false;
					flag_p2_attack1=false;
					count=0;
					radius=0;
					sourceX=248;
					source2X=521;
					source2Y=0;
					p1attack=false;
					p2attack=false;
					break;
			}
		}
	
	//*********************Player 1*************************
		
	frameCounter+=frameSpeed*clock.restart().asSeconds();
	if(frameCounter>=switchFrame)
	{
		frameCounter=0;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			p1sprite.setScale({ 1, 1 });
			sourceY=0;
			p1_movespeed=8;
			move(&p1sprite,&sourceX,&sourceY,&i,&p1_movespeed,49,420,248);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			p1sprite.setScale({ -1, 1 });
			sourceY=0;
			p1_movespeed=-8;
			move(&p1sprite,&sourceX,&sourceY,&i,&p1_movespeed,49,420,248);
			//std::cout<<sourceX<<std::endl;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			p1attack=true;
			p1sprite.setScale({ 1, 1 });
			if(flag_p1_attack1==false)
			{
				sourceX=5;
				sourceY=142;
				p1_movespeed=15;
			}
			move_attack(&p1sprite,&sourceX,&sourceY,&p1_movespeed,49,260,5);
			flag_p1_attack1=true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			p1attack=true;
			p1sprite.setScale({ -1, 1 });
			if(flag_p1_attack1==false)
			{
				sourceX=5;
				sourceY=142;
				p1_movespeed=-15;
			}
			move_attack(&p1sprite,&sourceX,&sourceY,&p1_movespeed,49,260,5);
			flag_p1_attack1=true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			p1attack=true;
			flag_p1_attack2=true;
			//std::cout<<"Vec size: "<<vec.size()<<std::endl;
			while(count<vec.size())
			{
				vec.at(count).setPosition(p1sprite.getPosition().x,350);
				count++;
			}
			radius++;
		}
		
		//std::cout<<"Distance "<<distance<<std::endl;
		if(distance!=-20)
		{
			distance--;
			p1sprite.move(0,-distance);
			if (p1sprite.getPosition().y==360)
			{
				distance=-20;
			}
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			distance=20;
		}
		//*******************Player 2**************************
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			p2sprite.setScale({ 1, 1 });
			source2Y=0;
			p2_movespeed=5;
			move(&p2sprite,&source2X,&source2Y,&i,&p2_movespeed,49,714,521);
			//std::cout<<"2X:"<<source2X<<std::endl;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			p2sprite.setScale({ -1, 1 });
			source2Y=0;
			p2_movespeed=-5;
			move(&p2sprite,&source2X,&source2Y,&i,&p2_movespeed,49,714,521);
			//std::cout<<"2X:"<<source2X<<std::endl;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			p2attack=true;
			p2sprite.setScale({ 1, 1 });
			if(flag_p2_attack1==false)
			{
				source2X=560;
				source2Y=258;
				p2_movespeed=5;
			}
			flag_p2_attack1=true;
			move_attack(&p2sprite,&source2X,&source2Y,&p2_movespeed,92,644,456);
			//usleep(100000);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			p2attack=true;
			p2sprite.setScale({ -1, 1 });
			if(flag_p2_attack1==false)
			{
				source2X=560;
				source2Y=258;
				p2_movespeed=-5;
			}
			flag_p2_attack1=true;
			move_attack(&p2sprite,&source2X,&source2Y,&p2_movespeed,92,644,456);
			//usleep(100000);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			p2attack=true;
			flag_p1_attack2=true;
			while(count<vec.size())
			{
				vec.at(count).setPosition(p2sprite.getPosition().x,350);
				count++;
			}
			radius++;
		}
		if(distance2!=-14)
		{
			distance2--;
			p2sprite.move(0,-distance2);
			if (p2sprite.getPosition().y==342)
			{
				distance2=-14;
			}
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			distance2=14;
		}
		
		//***********************Collision******************************
		if((p1sprite.getPosition().x-p2sprite.getPosition().x)<50 && (p1sprite.getPosition().x-p2sprite.getPosition().x)>-50)
		{
			collision1=true;
		}
		else
		{
			collision1=false;
		}
		
		if(collision1==true)
		{
			if (p1attack==true && p1sprite.getPosition().y>342 && p2sprite.getPosition().y>340)
			{
				std::cout<<"P1 Collision "<<p1sprite.getPosition().x-p2sprite.getPosition().x<<" ||"<<p1sprite.getPosition().x-p2sprite.getPosition().x<<std::endl;
				p2_movespeed=0;
				move(&p2sprite,&source2X,&source2Y,&i,&p2_movespeed,0,714,521);
				p1_movespeed=0;
				move(&p1sprite,&sourceX,&sourceY,&i,&p1_movespeed,0,714,521);
				
				
				if(l>=51)
				{
					p1win=true;
				}
				else
				{
					text2.setString(vec2.at(vec2.size()-1-l));
					l++;
					std::cout<<"Val of l: "<<l<<std::endl;
				}
				
			}
			//std::cout<<"collision y"<<p1sprite.getPosition().y<<std::endl;
			if (p2attack==true && p2sprite.getPosition().y>340 && p1sprite.getPosition().y>323)
			{
				std::cout<<"P1 Collision "<<p1sprite.getPosition().x-p2sprite.getPosition().x<<" ||"<<p1sprite.getPosition().x-p2sprite.getPosition().x<<std::endl;
				p2_movespeed=0;
				move(&p2sprite,&source2X,&source2Y,&i,&p2_movespeed,0,714,521);
				p1_movespeed=0;
				move(&p1sprite,&source2X,&source2Y,&i,&p2_movespeed,0,714,521);
				
				
				
				if(k>=51)
				{
					p2win=true;
				}
				else
				{
					text.setString(vec2.at(vec2.size()-1-k));
					k++;
				}
			}
		}
	}
	
	//****************************************************************
			p1sprite.setTextureRect(sf::IntRect(sourceX,sourceY,43,39));
		
			if(flag_p2_attack1==true)
			{
				p2sprite.setTextureRect(sf::IntRect(source2X,source2Y,76,70));
			}
			else
			{
				p2sprite.setTextureRect(sf::IntRect(source2X,source2Y,46,58));
			}
			if(flag_p1_attack2==true && radius<60){window.draw(vec.at(radius));}
			
			if(p1win==true)
			{
				std::cout<<"P1 win"<<std::endl;
				window.draw(text3);
			}
			else if(p2win==true)
			{
				std::cout<<"P2 win"<<std::endl;
				window.draw(text4);
				window.draw(p2sprite);
				window.draw(p1sprite);
				window.draw(rectangle1);
				window.draw(rectangle2);
				window.draw(rectangle3);
				window.draw(rectangle4);
				window.draw(text2);
				window.draw(text);
				window.display();
				window.clear(sf::Color(153, 204, 255,50));
				sleep(3);
				exit(0);
			}
			window.draw(p2sprite);
			window.draw(p1sprite);
			window.draw(rectangle1);
			window.draw(rectangle2);
			window.draw(rectangle3);
			window.draw(rectangle4);
			window.draw(text2);
			window.draw(text);
			window.display();
			window.clear(sf::Color(153, 204, 255,50));
			
	}
	return(0);
}

