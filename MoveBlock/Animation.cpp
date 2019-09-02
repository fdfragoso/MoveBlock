#include "Animation.h"

Animation::Animation(Sprite *objPlayer, list<Sprite> *lstBlock, Scene *objScene)
{
   this->pPlayer = objPlayer;
   this->pBlock = lstBlock;
   this->pScene = objScene;
   this->vx = 0;
   this->vy = 0;
   this->pMove = false;
   this->blocosCaindo = false;
   this->gameOver = false;
   this->contLinha = 0;
}

Animation::~Animation()
{

}

void Animation::Initialize()
{
   srand(time(0));
}

void Animation::UpdatePlayer()
{
   SDL_Rect dest = pPlayer->getDest();
   SDL_Rect src = pPlayer->getSrc();

   // Nova posição do Player
   dest.x = dest.x + pPlayer->getVX();
   dest.y = dest.y + pPlayer->getVY();   

   // Não deixar sair da tela na horizontal
   if (dest.x < 0)
     dest.x = 0;
   else if (dest.x > pScene->getWidth() - 64) 
     dest.x = pScene->getWidth() - 64;

   // Não deixar sair da tela na vertical
   if (dest.y < 0) 
     dest.y = 0;
   else if (dest.y >= pScene->getHeight() - 128)
   {
     dest.y = pScene->getHeight() - 128;
     pPlayer->setMove(false);
   }

   // Animação do pulo
   /*if (pPlayer->getJump())
   {
      if (dest.y <= pScene->getHeight() - 256)
	  {
		  pPlayer->setJump(false);
	      pPlayer->stopMovingDown();
	  }
   }
   else
   {*/
	  
      /*list<Sprite>::iterator it2 = this->pBlock->begin();
      for (it2 = pBlock->begin(); it2 != pBlock->end(); it2++)
	  {
		  int x = 128;
		  if(!it2->getCaindo())
		  {
			  if(isDownCollision(pPlayer->getDest(), it2->getDest()))
			  {
				  x += it2->getDest().y;
				  if (dest.y < pScene->getHeight() - x)
					   dest.y = dest.y + 32;
			  }
			  else
			  {
				 if (dest.y < pScene->getHeight() - 128)
					dest.y = dest.y + 32;
			  }
		  }
		  else
		  {
				if (dest.y < pScene->getHeight() - 128)
					dest.y = dest.y + 32;
		  }
	  }*/
 
	/*   if (dest.y < pScene->getHeight() - 128)
					dest.y = dest.y + 16;
		 */
	   
   //}

   if (pPlayer->getColidiu())
   {
      pPlayer->setVX(0);
      pPlayer->setColidiu(false);
   }

   // Atualiza propriedades do Player
   pPlayer->setDest(dest);
   pPlayer->setSrc(src);

   // Verifica colisão
   list<Sprite>::iterator it = this->pBlock->begin();
   for (it = pBlock->begin(); it != pBlock->end(); it++)
      TestCollisionPlayer(&(*it));

   // Desenha personagem na tela
   SDL_BlitSurface(pPlayer->getImage(), &pPlayer->getSrc(), pScene->getScreen(), &pPlayer->getDest());  
}

void Animation::TestCollisionPlayer(Sprite *bloco)
{
   if (!pPlayer->getMove() && !bloco->getCaindo())
   {
      if (pPlayer->getDest().x > bloco->getDest().x)
      {
         if (isLeftCollision(pPlayer->getDest(), bloco->getDest()))
         {
            if (bloco->getMove())
            {
               bloco->setVX(-32);
               bloco->setMove(false);
            }
            else
            {
               pPlayer->setVX(16);
               pPlayer->setColidiu(true);
            }
         }
         else
            bloco->setMove(true);
      }
      else
      {
         if (isRightCollision(pPlayer->getDest(), bloco->getDest()))
         {
            if (bloco->getMove())
            {
               bloco->setVX(32);
               bloco->setMove(false);
            }
            else
            {
               pPlayer->setVX(-16);
               pPlayer->setColidiu(true);
            }
         }
         else
            bloco->setMove(true);
      }
   }

    // Verifica se o bloco está caindo
    if(bloco->getCaindo())
    {
        // verifica se o bloco cai no personagem, se sim o jogo é finalizado	   
        if (isUpCollision(pPlayer->getDest(), bloco->getDest()) && isLeftCollision(pPlayer->getDest(), bloco->getDest()) && isRightCollision(pPlayer->getDest(), bloco->getDest()))
            this->gameOver = true;  
    }

    

}

void Animation::DeleteLine()
{
    list<Sprite>::iterator itDelline = this->pBlock->begin();
    for (itDelline = pBlock->begin(); itDelline != pBlock->end(); itDelline++) 
    {
        if (itDelline->getDest().y ==pScene->getHeight() - 64)
         {
             this->pBlock->erase(itDelline);
             itDelline = this->pBlock->begin();
             this->lineDelete = true;
          } 
    }
    itDelline = this->pBlock->begin();
    if (itDelline->getDest().y == 536)
        this->pBlock->erase(itDelline);
}

void Animation::UpdateBlock()
{
	
    int a = 0;
    //verifica se existe algum bloco caindo    
    if (!blocosCaindo) 
    {
        //gera numero aleatorio de 0 a 12
        int x = (rand() % (12));
        //cria um novo bloco
        Sprite *objBlock = new Sprite();
        objBlock->Initialize("img_block.bmp");
        //verifica onde ele vai cair
        SDL_Rect dest = objBlock->getDest();
        dest.x = x * 64;
        objBlock->setDest(dest);
        //incluí o src com x negativo pra não ocorrer aquele problema dos blocos travarem
        SDL_Rect src = objBlock->getSrc();
        //src.x = x - 128; 
        objBlock->setSrc(src);
        //adiciona a lista
        pBlock->push_back(*objBlock);
        this->blocosCaindo = true;
    }

    //animação do bloco caindo
    list<Sprite>::iterator it2 = this->pBlock->begin();
    list<Sprite>::iterator it = this->pBlock->begin();
    for (it = pBlock->begin(); it != pBlock->end(); it++) 
    {
        if (a==1)
        {
            it = pBlock->begin();
            a = 0;
        }
        SDL_Rect dest = (*it).getDest();
        SDL_Rect src = (*it).getSrc();
        //verifica se o bloco está caindo
        if ((*it).getCaindo()) 
        {
            //soma ao y para ele cair  
            dest.y += 8;
            //pega a altura da tela - tamanho do bloco
            if (dest.y > pScene->getHeight() - 64)
            {
                //se chegar ao fim fala que este bloco parou de cair
                (*it).setCaindo(false);
                //essa variavel fala ao game loop que o bloco parou e um novo precisa ser inserido na lista
               	this->blocosCaindo = false;
                this->contLinha +=1;
            }                

            //Falta colocar uma varredura de todos os blocos.
             for (it2 = pBlock->begin(); it2 != pBlock->end(); it2++) 
             {
               if (it2->getCaindo() == false)
                {
                    if (it->getDest().x == it2->getDest().x)
                    {
                        if ((it->getDest().y == it2->getDest().y-64) || (it == pBlock->begin()))
                        {
                            (*it).setCaindo(false);
                            this->blocosCaindo = VerificaCaindo();
                            if (it->getDest().y < 64)
                                this->gameOver = true;
                        }
                        
                    }
                }
               
             }
        }
        //Tive que adicionar edsssa parte para contornar um erro na atribuiçao do x e y
        //if (this->blocosCaindo == true)
        if (it->getCaindo() == true)
        {   int a = dest.y;
            src.y = a;
            (*it).setDest(dest);
            (*it).setSrc(src);
        }
        if (contLinha == 12)
        {
            this->DeleteLine();
            contLinha = 0;
        }    
        //desenha na tela
        if (this->lineDelete == false) {
        SDL_BlitSurface((*it).getImage(), NULL, pScene->getScreen(), &(*it).getDest());
        }
        else
        if (this->lineDelete == true) {
            a=1;
            it = this->pBlock->begin();
            //faz os demais blocos cairem
            list<Sprite>::iterator itCair = this->pBlock->begin();
            for (itCair = this->pBlock->begin(); itCair != this->pBlock->end(); itCair++) 
            {
                itCair->setCaindo(true);
            }
        }
        this->blocosCaindo = VerificaCaindo();
        this->lineDelete = false;       
    }	

    //Desenha os blocos que forem empurrados
    it = 0;
    list<Sprite>::iterator it3 = this->pBlock->begin();
    for (it = pBlock->begin(); it != pBlock->end(); it++) 
    {
        bool colidiu = false;
        for (it3 = pBlock->begin(); it3 != pBlock->end(); it3++) 
        {
            if ((it != it3) && (isCollision((*it).getDest(), (*it3).getDest())))
                colidiu = true;
        }
        if (!colidiu)
            MoveBlock(&(*it));

        it3 = 0;
    }
}

void Animation::MoveBlock(Sprite *bloco)
{
   SDL_Rect dest = bloco->getDest();
   SDL_Rect src = bloco->getSrc();

   // Nova posição do Block
   dest.x = dest.x + bloco->getVX();
   dest.y = dest.y + bloco->getVY();   

   // Não deixar sair da tela na horizontal
   if (dest.x < 0)
     dest.x = 0;
   else if (dest.x > pScene->getWidth() - (64 + 32)) 
     dest.x = pScene->getWidth() - (64 + 32);

   // Não deixar sair da tela na vertical
   if (dest.y < 0) 
     dest.y = 0;
   else if (dest.y > pScene->getHeight() - 64)
     dest.y = pScene->getHeight() - 64;

   // Atualiza propriedades do Block
   bloco->setDest(dest);
   bloco->setSrc(src);

   // Se estiver movendo, para de se mover
   if (bloco->getMove())
      bloco->setVX(0);

   // Desenha personagem na tela
   SDL_BlitSurface(bloco->getImage(), &bloco->getSrc(), pScene->getScreen(), &bloco->getDest()); 
}

bool Animation::VerificaCaindo()
{
    list<Sprite>::iterator itVerifica = this->pBlock->begin();
    for (itVerifica = pBlock->begin(); itVerifica != pBlock->end(); itVerifica++) 
    {
        if (itVerifica->getCaindo() == true)
        {
            return true;
            break;
        }
    }
}


void Animation::Jump()
{
   SDL_Rect dest = pPlayer->getDest();
   // Animação do pulo
   if (pPlayer->getJump())
   {
      if (dest.y <= pScene->getHeight() - 256)
	  {
		  pPlayer->setJump(false);
	      pPlayer->stopMovingDown();
	  }
   }
   else
   {
	  
      list<Sprite>::iterator it2 = this->pBlock->begin();
      for (it2 = pBlock->begin(); it2 != pBlock->end(); it2++)
	  {
		  int x = 128;
		  if(!it2->getCaindo())
		  {
			  if(isDownCollision(pPlayer->getDest(), it2->getDest()))
			  {
				  x += it2->getDest().y;
				  if (dest.y < pScene->getHeight() - x)
					   dest.y = dest.y + 32;
			  }
			  else
			  {
				 if (dest.y < pScene->getHeight() - 128)
					dest.y = dest.y + 32;
			  }
		  }
		  else
		  {
				if (dest.y < pScene->getHeight() - 128)
					dest.y = dest.y + 32;
		  }
	  }
 
	   if (dest.y < pScene->getHeight() - 128)
					dest.y = dest.y + 16;
		 
	   
   }
}