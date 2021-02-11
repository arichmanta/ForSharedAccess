//ot podskazchika, esli how poprobui takoi metod
// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;
    float time = float(timer.GetTotalSeconds());


    RECT WindowRect;
    GetClientRect(m_window, &WindowRect);
    MapWindowPoints(m_window, NULL, (LPPOINT)&WindowRect, 2);
    if (ActiveApp)
    {
        GetCursorPos(&CursorPos);
		// WindowRect.right - (m_outputWidth / 2)) Eto dlya centralizacii mouse
        PosToCameraAngle.x += (CursorPos.x - (WindowRect.right - (m_outputWidth / 2))) * 0.1;

        PosToCameraAngle.z += (CursorPos.y - (WindowRect.bottom - (m_outputHeight / 2))) * 0.1;

        if (PosToCameraAngle.z < -89)
            PosToCameraAngle.z = -89;
        if (PosToCameraAngle.z > 89)
            PosToCameraAngle.z = 89;

        if (PosToCameraAngle.x > 180)
            PosToCameraAngle.x = -179.999;
        if (PosToCameraAngle.x < -180)
            PosToCameraAngle.x = 179.999;
        
        PosToCameraAngle.y = PosToCameraAngle.x;
//lishnee
        //if (PosToCameraAngle.z > 180)
          //  PosToCameraAngle.z = -179.999;
        //if (PosToCameraAngle.z < -180)
          //  PosToCameraAngle.z = 179.999;

	//dvijenie po okrujnosti osi XY
        AngleCameraX = cos(PosToCameraAngle.x * XM_PI / 180); //znachenie ot -1 do 1
        AngleCameraY = sin(PosToCameraAngle.y * XM_PI / 180); //znachenie ot -1 do 1
	//metod gde mi sovershaem cursorom dvizhenie po okrujnosti osi ZY po analogii s XY
	AngleCameraZY = cos(PosToCameraAngle.z * XM_PI / 180); //znachenie ot 0 do 1
	//navernoe tut -sin sudya potomu kakoi u tebya znak u tan bil iz za invertirovaniya no eto ne tochno Kappa da i cos s sin ya mogu putat po etomu srazu ne napisal pravilno
        AngleCameraZ = -sin(PosToCameraAngle.z * XM_PI / 180); //znachenie ot -1 do 1
	//sumiruev offseti smejnih osei
	AngleCameraY+=AngleCameraZY;
	 
	//est eshe mikroshans chto tak ne srabotaet i nado dobavliat smejnui ZX a ne ZY i togda budet tak vmesto togo chto vishe
	//AngleCameraX+=AngleCameraZY;
	    
	//tak kak mi privodim dvizhenie po edenichnoi okrujnosti dvijenie vverh mi obiazani priviasat k visote modeli
	AngleCameraZ *= model_height/1.5;
	//jelatelno takuiu je privasku sdelat i k XY vzyav bolwee iz shirini i dlini modeli
	AngleCameraX *= max(model_length, model_width)/1.5;
	AngleCameraY *= max(model_length, model_width)/1.5;
	
		//vozvrashaem kursor v center
        SetCursorPos(WindowRect.right - (m_outputWidth / 2), WindowRect.bottom - (m_outputHeight / 2));

        //position control dlya input keyboard
        {
            if (m_pos.m_keyA) 
            {
                m_pos.posX += AngleCameraY;
                m_pos.posY -= AngleCameraX;
            }
            if (m_pos.m_keyW)
            {
                m_pos.posX += AngleCameraX;
                m_pos.posY += AngleCameraY;
            }
            if (m_pos.m_keyD)
            {
                m_pos.posX -= AngleCameraY;
                m_pos.posY += AngleCameraX;
            }
            if (m_pos.m_keyS)
            {
                m_pos.posX -= AngleCameraX;
                m_pos.posY -= AngleCameraY;
            }

            if (m_pos.m_keyUp)
            {
                m_pos.posZ++;
            }

            if (m_pos.m_keyDown)
            {
                m_pos.posZ--;
            }

            if (m_pos.m_keyZero)
            {
                m_pos.posX = 0;
                m_pos.posY = 0;
            }
        }
    }

	//Sama matriza zdes.
    m_view = Matrix::CreateLookAt(Vector3(m_pos.posX, m_pos.posZ+0.1f, m_pos.posY),
        Vector3(AngleCameraX + m_pos.posX, AngleCameraZ + m_pos.posZ, AngleCameraY + m_pos.posY), Vector3::UnitY);

}
