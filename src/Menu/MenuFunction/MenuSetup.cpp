#include "MenuSetup.h"

void MenuSetup::setupDialogueRenderer(Menu* menu, DialogueRendererData* dialogueData)
{
	Overlay dialogue(menu->getRenderer());

	TextBox* topLine = new TextBox;
	TextBox* botLine = new TextBox;

	topLine->dynamic_text = &dialogueData->topLine;
	botLine->dynamic_text = &dialogueData->bottomLine;

	topLine->renderData = TextBoxRenderData{ 4.0f, 12.0f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };
	botLine->renderData = TextBoxRenderData{ 4.0f, 4.0f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };

	dialogue.addTextBox(topLine);
	dialogue.addTextBox(botLine);

	TextBox* speakerName = new TextBox;
	speakerName->dynamic_text = &dialogueData->speakerName;
	speakerName->renderData = TextBoxRenderData{ 5.5f, 22.5f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };
	dialogue.addTextBox(speakerName);

	dialogue.addPolygon(&dialogueData->nameOutline);

	dialogue.addImage(&dialogueData->nextArrow);

	Button* topButton = new Button;
	Button* bottomButton = new Button;

	topButton->active = &dialogueData->buttonActiveStatus;
	bottomButton->active = &dialogueData->buttonActiveStatus;

	topButton->dynamic_text = &dialogueData->topButtonOption;
	bottomButton->dynamic_text = &dialogueData->bottomButtonOption;

	topButton->down = bottomButton;
	topButton->up = bottomButton;

	bottomButton->up = topButton;
	bottomButton->down = topButton;

	topButton->data = (int)true;
	bottomButton->data = (int)false;

	topButton->dynamicRenderData = &dialogueData->topButtonRenderData;
	bottomButton->dynamicRenderData = &dialogueData->bottomButtonRenderData;

	dialogue.addButton(topButton);
	dialogue.addButton(bottomButton);

	menu->add(MenuOverlay::DIALOGUE, dialogue);
}

void MenuSetup::setupKeyboard(Menu* menu, AlphabetStringData* alphabet, std::string* input)
{
	//std::cout << "Input Memory Location Setup: " << input << std::endl;
	//std::cout << "Alphabet Memory Location Setup: " << alphabet << std::endl;

	Overlay onScreenKeyboard(menu->getRenderer());

	TextBox* keyboardInput = new TextBox;

	keyboardInput->dynamic_text = input;

	Button* a = new Button;
	Button* b = new Button;
	Button* c = new Button;
	Button* d = new Button;
	Button* e = new Button;
	Button* f = new Button;
	Button* g = new Button;
	Button* h = new Button;
	Button* i = new Button;
	Button* j = new Button;
	Button* k = new Button;
	Button* l = new Button;
	Button* m = new Button;
	Button* n = new Button;
	Button* o = new Button;
	Button* p = new Button;
	Button* q = new Button;
	Button* r = new Button;
	Button* s = new Button;
	Button* t = new Button;
	Button* u = new Button;
	Button* v = new Button;
	Button* w = new Button;
	Button* x = new Button;
	Button* y = new Button;
	Button* z = new Button;

	Button* colon = new Button;
	Button* apostrophe = new Button;

	Button* one = new Button;
	Button* two = new Button;
	Button* three = new Button;
	Button* four = new Button;
	Button* five = new Button;
	Button* six = new Button;
	Button* seven = new Button;
	Button* eight = new Button;
	Button* nine = new Button;
	Button* zero = new Button;

	Button* shift = new Button;
	Button* space = new Button;
	Button* del = new Button;
	Button* enter = new Button;

	// Text
	{
		a->dynamic_text = &alphabet->a_f.string1;
		b->dynamic_text = &alphabet->a_f.string2;
		c->dynamic_text = &alphabet->a_f.string3;
		d->dynamic_text = &alphabet->a_f.string4;
		e->dynamic_text = &alphabet->a_f.string5;
		f->dynamic_text = &alphabet->a_f.string6;
		g->dynamic_text = &alphabet->g_l.string1;
		h->dynamic_text = &alphabet->g_l.string2;
		i->dynamic_text = &alphabet->g_l.string3;
		j->dynamic_text = &alphabet->g_l.string4;
		k->dynamic_text = &alphabet->g_l.string5;
		l->dynamic_text = &alphabet->g_l.string6;
		m->dynamic_text = &alphabet->m_r.string1;
		n->dynamic_text = &alphabet->m_r.string2;
		o->dynamic_text = &alphabet->m_r.string3;
		p->dynamic_text = &alphabet->m_r.string4;
		q->dynamic_text = &alphabet->m_r.string5;
		r->dynamic_text = &alphabet->m_r.string6;
		s->dynamic_text = &alphabet->s_x.string1;
		t->dynamic_text = &alphabet->s_x.string2;
		u->dynamic_text = &alphabet->s_x.string3;
		v->dynamic_text = &alphabet->s_x.string4;
		w->dynamic_text = &alphabet->s_x.string5;
		x->dynamic_text = &alphabet->s_x.string6;
		y->dynamic_text = &alphabet->y_z.string1;
		z->dynamic_text = &alphabet->y_z.string2;

		one->text = "1";
		two->text = "2";
		three->text = "3";
		four->text = "4";
		five->text = "5";
		six->text = "6";
		seven->text = "7";
		eight->text = "8";
		nine->text = "9";
		zero->text = "0";

		colon->text = ":";
		apostrophe->text = "\'";

		del->text = "Del";
		enter->text = "Enter";
	}

	// Data
	{
		a->data = 1;
		b->data = 2;
		c->data = 3;
		d->data = 4;
		e->data = 5;
		f->data = 6;
		g->data = 7;
		h->data = 8;
		i->data = 9;
		j->data = 10;
		k->data = 11;
		l->data = 12;
		m->data = 13;
		n->data = 14;
		o->data = 15;
		p->data = 16;
		q->data = 17;
		r->data = 18;
		s->data = 19;
		t->data = 20;
		u->data = 21;
		v->data = 22;
		w->data = 23;
		x->data = 24;
		y->data = 25;
		z->data = 26;

		colon->data = 27;
		apostrophe->data = 28;

		one->data = 29;
		two->data = 30;
		three->data = 31;
		four->data = 32;
		five->data = 33;
		six->data = 34;
		seven->data = 35;
		eight->data = 36;
		nine->data = 37;
		zero->data = 38;

		shift->data = 39;
		space->data = 40;
		del->data = 41;
		enter->data = 42;
	}

	// Link Elements
	{
		// Number Row
		{
			one->down = q;
			one->right = two;
			two->down = w;
			two->left = one;
			two->right = three;
			three->left = two;
			three->down = e;
			three->right = four;
			four->left = three;
			four->down = r;
			four->right = five;
			five->left = four;
			five->down = t;
			five->right = six;
			six->left = five;
			six->down = y;
			six->right = seven;
			seven->left = six;
			seven->down = u;
			seven->right = eight;
			eight->left = seven;
			eight->down = i;
			eight->right = nine;
			nine->left = eight;
			nine->down = o;
			nine->right = zero;
			zero->left = nine;
			zero->down = p;
		}

		// Colon Row
		{
			colon->up = one;
			colon->down = shift;
			colon->right = q;

			q->up = one;
			q->down = a;
			q->left = colon;
			q->right = w;

			w->up = two;
			w->down = s;
			w->left = q;
			w->right = e;

			e->up = three;
			e->down = d;
			e->left = w;
			e->right = r;

			r->up = four;
			r->down = f;
			r->left = e;
			r->right = t;

			t->up = five;
			t->down = g;
			t->left = r;
			t->right = y;

			y->up = six;
			y->down = h;
			y->left = t;
			y->right = u;

			u->up = seven;
			u->down = j;
			u->left = y;
			u->right = i;

			i->up = eight;
			i->down = k;
			i->left = u;
			i->right = o;

			o->up = nine;
			o->down = l;
			o->left = i;
			o->right = p;

			p->up = zero;
			p->down = del;
			p->left = o;
			p->right = apostrophe;

			apostrophe->up = zero;
			apostrophe->down = del;
			apostrophe->left = p;
		}

		// A Row
		{
			shift->up = colon;
			shift->down = space;
			shift->right = a;

			a->up = q;
			a->down = z;
			a->left = shift;
			a->right = s;

			s->up = w;
			s->down = z;
			s->left = a;
			s->right = d;

			d->up = e;
			d->down = x;
			d->left = s;
			d->right = f;

			f->up = r;
			f->down = c;
			f->left = d;
			f->right = g;

			g->up = t;
			g->down = v;
			g->left = f;
			g->right = h;

			h->up = y;
			h->down = b;
			h->left = g;
			h->right = j;

			j->up = u;
			j->down = n;
			j->left = h;
			j->right = k;

			k->up = i;
			k->down = m;
			k->left = j;
			k->right = l;

			l->up = o;
			l->down = m;
			l->left = k;
			l->right = del;

			del->up = p;
			del->down = enter;
			del->left = l;
		}

		// Z Row
		{
			z->up = s;
			z->down = space;
			z->left = shift;
			z->right = x;

			x->up = d;
			x->down = space;
			x->left = z;
			x->right = c;

			c->up = f;
			c->down = space;
			c->left = x;
			c->right = v;

			v->up = g;
			v->down = space;
			v->left = c;
			v->right = b;

			b->up = h;
			b->down = space;
			b->left = v;
			b->right = n;

			n->up = j;
			n->down = space;
			n->left = b;
			n->right = m;

			m->up = k;
			m->down = space;
			m->left = n;
			m->right = enter;

			enter->up = del;
			enter->left = m;
			enter->down = space;

			space->up = v;
			space->left = shift;
			space->right = enter;
		}

	}

	{}	// The render data tab in visual studio wont collapse without it lol

	// Render Data
	{
		float spacing = 1.82f;
		float buttonSize = 5.0f;

		float bottomPadding = 10.0f;
		float leftPadding = (100 - ((12 * buttonSize) + (11 * spacing))) / 2.0f;
		float spaceBarMultiplier = 9.0f;

		Color buttonColor = Color::RED;

		space->renderData = ButtonRenderData{ 50.0f, bottomPadding + (buttonSize / 2.0f), buttonSize * spaceBarMultiplier, buttonSize, buttonColor };
		shift->renderData = ButtonRenderData{ leftPadding + buttonSize / 2.0f , space->renderData.percentageY + (buttonSize / 2.0f) + spacing + buttonSize + (spacing / 2.0f), buttonSize, (buttonSize * 2) + spacing, buttonColor };
		colon->renderData = ButtonRenderData{ shift->renderData.percentageX, shift->renderData.percentageY + (shift->renderData.heightPercent / 2.0f) + spacing + (buttonSize / 2.0f), buttonSize, buttonSize, buttonColor };
		q->renderData = ButtonRenderData{ colon->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY, buttonSize, buttonSize, buttonColor };
		w->renderData = ButtonRenderData{ q->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		e->renderData = ButtonRenderData{ w->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		r->renderData = ButtonRenderData{ e->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		t->renderData = ButtonRenderData{ r->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		y->renderData = ButtonRenderData{ t->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		u->renderData = ButtonRenderData{ y->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		i->renderData = ButtonRenderData{ u->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		o->renderData = ButtonRenderData{ i->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		p->renderData = ButtonRenderData{ o->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		apostrophe->renderData = ButtonRenderData{ p->renderData.percentageX + buttonSize + spacing, colon->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		a->renderData = ButtonRenderData{ q->renderData.percentageX, q->renderData.percentageY - buttonSize - spacing, buttonSize, buttonSize, buttonColor };
		s->renderData = ButtonRenderData{ a->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY, buttonSize, buttonSize, buttonColor };
		d->renderData = ButtonRenderData{ s->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		f->renderData = ButtonRenderData{ d->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		g->renderData = ButtonRenderData{ f->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		h->renderData = ButtonRenderData{ g->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		j->renderData = ButtonRenderData{ h->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		k->renderData = ButtonRenderData{ j->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		l->renderData = ButtonRenderData{ k->renderData.percentageX + buttonSize + spacing, a->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		del->renderData = ButtonRenderData{ l->renderData.percentageX + (buttonSize / 2.0f) + spacing + buttonSize + (spacing / 2.0f), a->renderData.percentageY, (buttonSize * 2) + spacing, buttonSize, buttonColor };
		z->renderData = ButtonRenderData{ s->renderData.percentageX, s->renderData.percentageY - buttonSize - spacing, buttonSize, buttonSize, buttonColor };
		x->renderData = ButtonRenderData{ z->renderData.percentageX + buttonSize + spacing, z->renderData.percentageY,buttonSize, buttonSize,  buttonColor };
		c->renderData = ButtonRenderData{ x->renderData.percentageX + buttonSize + spacing, z->renderData.percentageY,buttonSize, buttonSize,  buttonColor };
		v->renderData = ButtonRenderData{ c->renderData.percentageX + buttonSize + spacing, z->renderData.percentageY,buttonSize, buttonSize,  buttonColor };
		b->renderData = ButtonRenderData{ v->renderData.percentageX + buttonSize + spacing, z->renderData.percentageY,buttonSize, buttonSize,  buttonColor };
		n->renderData = ButtonRenderData{ b->renderData.percentageX + buttonSize + spacing, z->renderData.percentageY,buttonSize, buttonSize,  buttonColor };
		m->renderData = ButtonRenderData{ n->renderData.percentageX + buttonSize + spacing, z->renderData.percentageY,buttonSize, buttonSize,  buttonColor };

		enter->renderData = ButtonRenderData{ del->renderData.percentageX, del->renderData.percentageY - buttonSize - spacing, buttonSize * 2, buttonSize, buttonColor };

		one->renderData = ButtonRenderData{ q->renderData.percentageX, q->renderData.percentageY + buttonSize + spacing,buttonSize, buttonSize, buttonColor };
		two->renderData = ButtonRenderData{ one->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		three->renderData = ButtonRenderData{ two->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		four->renderData = ButtonRenderData{ three->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		five->renderData = ButtonRenderData{ four->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		six->renderData = ButtonRenderData{ five->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		seven->renderData = ButtonRenderData{ six->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		eight->renderData = ButtonRenderData{ seven->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		nine->renderData = ButtonRenderData{ eight->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };
		zero->renderData = ButtonRenderData{ nine->renderData.percentageX + buttonSize + spacing, one->renderData.percentageY,buttonSize, buttonSize, buttonColor };

		keyboardInput->renderData = TextBoxRenderData{ leftPadding - buttonSize + 3.0f, 65.0f, 10.0f, Color::BLACK, Alignment::LEFT_ALIGN };
	}

	// Add Elements
	{
		onScreenKeyboard.addButton(a);
		onScreenKeyboard.addButton(b);
		onScreenKeyboard.addButton(c);
		onScreenKeyboard.addButton(d);
		onScreenKeyboard.addButton(e);
		onScreenKeyboard.addButton(f);
		onScreenKeyboard.addButton(g);
		onScreenKeyboard.addButton(h);
		onScreenKeyboard.addButton(i);
		onScreenKeyboard.addButton(j);
		onScreenKeyboard.addButton(k);
		onScreenKeyboard.addButton(l);
		onScreenKeyboard.addButton(m);
		onScreenKeyboard.addButton(n);
		onScreenKeyboard.addButton(o);
		onScreenKeyboard.addButton(p);
		onScreenKeyboard.addButton(q);
		onScreenKeyboard.addButton(r);
		onScreenKeyboard.addButton(s);
		onScreenKeyboard.addButton(t);
		onScreenKeyboard.addButton(u);
		onScreenKeyboard.addButton(v);
		onScreenKeyboard.addButton(w);
		onScreenKeyboard.addButton(x);
		onScreenKeyboard.addButton(y);
		onScreenKeyboard.addButton(z);
		onScreenKeyboard.addButton(colon);
		onScreenKeyboard.addButton(apostrophe);
		onScreenKeyboard.addButton(one);
		onScreenKeyboard.addButton(two);
		onScreenKeyboard.addButton(three);
		onScreenKeyboard.addButton(four);
		onScreenKeyboard.addButton(five);
		onScreenKeyboard.addButton(six);
		onScreenKeyboard.addButton(seven);
		onScreenKeyboard.addButton(eight);
		onScreenKeyboard.addButton(nine);
		onScreenKeyboard.addButton(zero);
		onScreenKeyboard.addButton(shift);
		onScreenKeyboard.addButton(space);
		onScreenKeyboard.addButton(del);
		onScreenKeyboard.addButton(enter);
	}

	onScreenKeyboard.addTextBox(keyboardInput);
	menu->add(MenuOverlay::ON_SCREEN_KEYBOARD, onScreenKeyboard);
}

void MenuSetup::setupIntroData(Menu* menu, bool* studioVisible, bool* pressAnyButtonVisible, bool* showMaleIcon, bool* showFemaleIcon)
{
	{
		Scene introLinksScene(menu->getRenderer());
		introLinksScene.setBackgroundPath(g_sceneTextureLocations[MenuScene::INTRO_LINKS]);
		menu->add(MenuScene::INTRO_LINKS, introLinksScene);
	}

	{
		Scene introStudio(menu->getRenderer());
		introStudio.setBackgroundPath(g_sceneTextureLocations[MenuScene::INTRO_STUDIO]);
		menu->add(MenuScene::INTRO_STUDIO, introStudio);
	}

	{
		Scene introStudioCrown(menu->getRenderer());
		introStudioCrown.setBackgroundPath(g_sceneTextureLocations[MenuScene::INTRO_STUDIO_CROWN]);
		menu->add(MenuScene::INTRO_STUDIO_CROWN, introStudioCrown);
	}

	{
		Scene introLegendaryPokemon(menu->getRenderer());
		introLegendaryPokemon.setBackgroundPath(g_sceneTextureLocations[MenuScene::INTRO_LEGENDARY]);
		menu->add(MenuScene::INTRO_LEGENDARY, introLegendaryPokemon);
	}

	{
		Scene introPressAnyButton(menu->getRenderer());

		//introLegendaryScene.setBackgroundPath(g_sceneTextureLocations[MenuScene::INTRO_LEGENDARY]);

		TextBox* pressAnyButton = new TextBox;
		TextBox* pressAnyButtonOutline = new TextBox;
		TextBox* pokemonGameVersion = new TextBox;
		TextBox* pokemonGameVersionOutline = new TextBox;

		pressAnyButtonOutline->text = "PRESS ANY BUTTON";
		pressAnyButton->text = "PRESS ANY BUTTON";
		pokemonGameVersionOutline->text = "POKEMON PRIDE VERSION";
		pokemonGameVersion->text = "POKEMON PRIDE VERSION";

		pressAnyButtonOutline->visible = pressAnyButtonVisible;
		pressAnyButton->visible = pressAnyButtonVisible;

		float xPos = 50.0f;
		float yPos = 1.5f;

		float xDrop = 0.3f;
		float yDrop = 0.3f;

		float ySpacing = 12.0f;

		pokemonGameVersionOutline->renderData = TextBoxRenderData{ xPos - xDrop, yPos + ySpacing - yDrop, 3.0f, Color::BLACK };
		pokemonGameVersion->renderData = TextBoxRenderData{ xPos - xDrop, yPos + ySpacing - yDrop, 3.0f, Color::WHITE };
		pressAnyButtonOutline->renderData = TextBoxRenderData{ xPos - xDrop, yPos - yDrop, 3.0f, Color::BLACK };
		pressAnyButton->renderData = TextBoxRenderData{ xPos, yPos, 3.0f, Color::WHITE };


		introPressAnyButton.addTextBox(pokemonGameVersionOutline);
		introPressAnyButton.addTextBox(pokemonGameVersion);
		introPressAnyButton.addTextBox(pressAnyButtonOutline);
		introPressAnyButton.addTextBox(pressAnyButton);

		menu->add(MenuScene::INTRO_PRESS_ANY_BUTTON, introPressAnyButton);
	}

	{
		Scene playerNameScene(menu->getRenderer());
		playerNameScene.setBackgroundPath(g_sceneTextureLocations[MenuScene::SET_PLAYER_NAME]);

		TextBox* playerNameText = new TextBox;
		playerNameText->text = "NAME:";
		playerNameText->renderData = TextBoxRenderData{ 50.0f, 83.0f, 10.0f };
		playerNameScene.addTextBox(playerNameText);

		float imageXPercent = 5.0f;
		float imageYPercent = 93.0f;
		float imageSize = 0.4f;

		playerNameScene.addImage(new ImageRenderData{ imageXPercent, imageYPercent, imageSize * 9.0f, imageSize * 16.0f, g_overlayTextureLocations[MenuOverlay::MALE_GENDER_ICON], nullptr, showMaleIcon });
		playerNameScene.addImage(new ImageRenderData{ imageXPercent, imageYPercent, imageSize * 9.0f, imageSize * 16.0f, g_overlayTextureLocations[MenuOverlay::FEMALE_GENDER_ICON], nullptr, showFemaleIcon });

		menu->add(MenuScene::SET_PLAYER_NAME, playerNameScene);
	}

	{
		Scene professorMScene(menu->getRenderer());
		professorMScene.setBackgroundPath(g_sceneTextureLocations[MenuScene::PROFESSOR_M]);
		menu->add(MenuScene::PROFESSOR_M, professorMScene);
	}
}

void MenuSetup::setupStartupData(Menu* menu, SharedString* header1, SharedString* header2, SharedString* header3, bool* f1Visible, bool* f2Visible, bool* f3Visible)
{
	//Startup Scene
	{
		Scene startupScene(menu->getRenderer());
		startupScene.setBackgroundPath(g_sceneTextureLocations[MenuScene::STARTUP_SCENE]);

		Button* playFile1 = new Button;
		Button* playFile2 = new Button;
		Button* playFile3 = new Button;

		Button* deleteFile1 = new Button;
		Button* deleteFile2 = new Button;
		Button* deleteFile3 = new Button;

		TextBox* file1PlayerName = new TextBox;
		TextBox* file2PlayerName = new TextBox;
		TextBox* file3PlayerName = new TextBox;

		TextBox* file1PlayTime = new TextBox;
		TextBox* file2PlayTime = new TextBox;
		TextBox* file3PlayTime = new TextBox;

		TextBox* file1PokedexFound = new TextBox;
		TextBox* file2PokedexFound = new TextBox;
		TextBox* file3PokedexFound = new TextBox;

		TextBox* file1Badges = new TextBox;
		TextBox* file2Badges = new TextBox;
		TextBox* file3Badges = new TextBox;


		playFile1->data = 0;
		playFile2->data = 1;
		playFile3->data = 2;

		deleteFile1->data = 3;
		deleteFile2->data = 4;
		deleteFile3->data = 5;

		deleteFile1->overlay = MenuOverlay::DELETE_CONFIRMATION;
		deleteFile2->overlay = MenuOverlay::DELETE_CONFIRMATION;
		deleteFile3->overlay = MenuOverlay::DELETE_CONFIRMATION;

		playFile1->text = "PlAY";
		playFile2->text = "PlAY";
		playFile3->text = "PlAY";
		deleteFile1->text = "DElETE";
		deleteFile2->text = "DElETE";
		deleteFile3->text = "DElETE";


		playFile1->down = deleteFile1;
		playFile1->right = playFile2;

		playFile2->left = playFile1;
		playFile2->right = playFile3;
		playFile2->down = deleteFile2;

		playFile3->left = playFile2;
		playFile3->down = deleteFile3;

		deleteFile1->up = playFile1;
		deleteFile1->right = deleteFile2;

		deleteFile2->up = playFile2;
		deleteFile2->left = deleteFile1;
		deleteFile2->right = deleteFile3;

		deleteFile3->up = playFile3;
		deleteFile3->left = deleteFile2;

		deleteFile1->active = f1Visible;
		deleteFile2->active = f2Visible;
		deleteFile3->active = f3Visible;

		file1PlayerName->dynamic_text = &header1->string1;
		file2PlayerName->dynamic_text = &header2->string1;
		file3PlayerName->dynamic_text = &header3->string1;

		file1PlayTime->dynamic_text = &header1->string2;
		file2PlayTime->dynamic_text = &header2->string2;
		file3PlayTime->dynamic_text = &header3->string2;

		file1PokedexFound->dynamic_text = &header1->string3;
		file2PokedexFound->dynamic_text = &header2->string3;
		file3PokedexFound->dynamic_text = &header3->string3;

		file1Badges->dynamic_text = &header1->string4;
		file2Badges->dynamic_text = &header2->string4;
		file3Badges->dynamic_text = &header3->string4;


		playFile1->renderData = ButtonRenderData{ 20.0f, 50.0f, 10.0f, 5.0f, Color::GREEN };
		playFile2->renderData = ButtonRenderData{ 50.0f, 50.0f, 10.0f, 5.0f, Color::GREEN };
		playFile3->renderData = ButtonRenderData{ 80.0f, 50.0f, 10.0f, 5.0f, Color::GREEN };

		deleteFile1->renderData = ButtonRenderData{ 20.0f, 40.0f, 5.0f, 2.5f, Color::RED };
		deleteFile2->renderData = ButtonRenderData{ 50.0f, 40.0f, 5.0f, 2.5f, Color::RED };
		deleteFile3->renderData = ButtonRenderData{ 80.0f, 40.0f, 5.0f, 2.5f, Color::RED };


		file1PlayerName->renderData = TextBoxRenderData{ 20.0f, 70.0f, 2.0f };
		file2PlayerName->renderData = TextBoxRenderData{ 50.0f, 70.0f, 2.0f };
		file3PlayerName->renderData = TextBoxRenderData{ 80.0f, 70.0f, 2.0f };

		file1PlayTime->renderData = TextBoxRenderData{ 20.0f, 65.0f, 2.0f };
		file2PlayTime->renderData = TextBoxRenderData{ 50.0f, 65.0f, 2.0f };
		file3PlayTime->renderData = TextBoxRenderData{ 80.0f, 65.0f, 2.0f };

		file1PokedexFound->renderData = TextBoxRenderData{ 20.0f, 60.0f, 2.0f };
		file2PokedexFound->renderData = TextBoxRenderData{ 50.0f, 60.0f, 2.0f };
		file3PokedexFound->renderData = TextBoxRenderData{ 80.0f, 60.0f, 2.0f };

		file1Badges->renderData = TextBoxRenderData{ 20.0f, 55.0f, 2.0f };
		file2Badges->renderData = TextBoxRenderData{ 50.0f, 55.0f, 2.0f };
		file3Badges->renderData = TextBoxRenderData{ 80.0f, 55.0f, 2.0f };



		startupScene.addButton(playFile2);
		startupScene.addButton(playFile1);
		startupScene.addButton(playFile3);
		startupScene.addButton(deleteFile1);
		startupScene.addButton(deleteFile2);
		startupScene.addButton(deleteFile3);


		startupScene.addTextBox(file1PlayerName);
		startupScene.addTextBox(file2PlayerName);
		startupScene.addTextBox(file3PlayerName);

		startupScene.addTextBox(file1PlayTime);
		startupScene.addTextBox(file2PlayTime);
		startupScene.addTextBox(file3PlayTime);

		startupScene.addTextBox(file1PokedexFound);
		startupScene.addTextBox(file2PokedexFound);
		startupScene.addTextBox(file3PokedexFound);

		startupScene.addTextBox(file1Badges);
		startupScene.addTextBox(file2Badges);
		startupScene.addTextBox(file3Badges);

		menu->add(MenuScene::STARTUP_SCENE, startupScene);
	}


	// Delete Confirmation
	{
		Overlay deleteConfirmation(menu->getRenderer());
		deleteConfirmation.setOverlayBackground(new ImageRenderData{ 50.0f, 50.0f, 30.0f, 30.0f, g_overlayTextureLocations[MenuOverlay::DELETE_CONFIRMATION] });


		TextBox* confirmMessage = new TextBox;
		Button* yes = new Button;
		Button* no = new Button;

		confirmMessage->text = "Delete Save?";
		yes->text = "YES";
		no->text = "NO";

		yes->right = no;
		no->left = yes;


		yes->data = 0;
		no->data = 1;


		confirmMessage->renderData = TextBoxRenderData{ 50.0f, 55.0f, 5.0f };
		yes->renderData = ButtonRenderData{ 45.0f, 45.0f, 10.0f, 7.5f };
		no->renderData = ButtonRenderData{ 55.0f, 45.0f, 10.0f, 7.5f };

		deleteConfirmation.addButton(no);
		deleteConfirmation.addButton(yes);
		deleteConfirmation.addTextBox(confirmMessage);

		menu->add(MenuOverlay::DELETE_CONFIRMATION, deleteConfirmation);
	}
}

void MenuSetup::setupBattleData(Menu* menu, SharedString* moves, SimulationCommand* menuCommand, RosterDisplayData* rosterData, ItemDisplayData* battleItemData, BattlePokemonData* battleData, DynamicImageRenderData* playerPokemon, DynamicImageRenderData* oppPokemon, LearnMoveData* learnMoveData)
{
	//		Main Battle
	{
		Scene mainBattle(menu->getRenderer());
		mainBattle.setBackgroundPath(g_sceneTextureLocations[MenuScene::BATTLE]);

		mainBattle.addDynamicImage(playerPokemon);
		mainBattle.addDynamicImage(oppPokemon);

		TextBox* playerName = new TextBox;
		TextBox* opponentName = new TextBox;

		TextBox* playerLevel = new TextBox;
		TextBox* opponentLevel = new TextBox;

		TextBox* currentHP = new TextBox;
		TextBox* maxHP = new TextBox;

		playerName->dynamic_text = &battleData->playerName;
		opponentName->dynamic_text = &battleData->opponentName;

		playerLevel->dynamic_text = &battleData->playerLevel;
		opponentLevel->dynamic_text = &battleData->opponentLevel;

		currentHP->dynamic_text = &battleData->currentHP;
		maxHP->dynamic_text = &battleData->maxHP;


		playerName->renderData = TextBoxRenderData{ 53.0f, 45.0f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		opponentName->renderData = TextBoxRenderData{ 1.0f, 77.5f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };

		playerLevel->renderData = TextBoxRenderData{ 98.0f, 45.0f, 5.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		opponentLevel->renderData = TextBoxRenderData{ 38.0f, 77.5f, 5.0f, Color::BLACK, Alignment::RIGHT_ALIGN };

		currentHP->renderData = TextBoxRenderData{ 85.0f, 30.0f, 5.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		maxHP->renderData = TextBoxRenderData{ 86.5f, 30.0f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };

		mainBattle.addTextBox(playerName);
		mainBattle.addTextBox(opponentName);
		mainBattle.addTextBox(playerLevel);
		mainBattle.addTextBox(opponentLevel);
		mainBattle.addTextBox(currentHP);
		mainBattle.addTextBox(maxHP);


		float yMultiplier = (1080.0f / 563.0f);
		float xMultiplier = (1920.0f / 1000.0f);

		//TODO: Use normal measuements
		mainBattle.addRectangle(new RectangleRenderData{ (745.0f / 1920.0f) * 100 * xMultiplier, (221.0f / 1080.0f) * 100 * yMultiplier, (27.0f / 1080.0f) * 100 * yMultiplier, &battleData->playerCurHPPercent });
		mainBattle.addRectangle(new RectangleRenderData{ (187.0f / 1920.0f) * 100 * xMultiplier, (414.0f / 1080.0f) * 100 * yMultiplier, (24.0f / 1080.0f) * 100 * yMultiplier, &battleData->opponentCurHPPercent });
		mainBattle.addRectangle(new RectangleRenderData{ (587.0f / 1920.0f) * 100 * xMultiplier, (159.0f / 1080.0f) * 100 * yMultiplier, (14.0f / 1080.0f) * 100 * yMultiplier, &battleData->playerXPPercent, Color::BLUE });


		// Major Status Condition

		float statusWidth = 6.0f;
		float statusHeight = statusWidth / 2.0f;

		mainBattle.addImage(new ImageRenderData{ 60.0f, 40.0f, statusWidth, statusHeight, "", &battleData->playerMajorStatusTexture });
		mainBattle.addImage(new ImageRenderData{ 6.5f, 74.5f, statusWidth, statusHeight, "", &battleData->opponentMajorStatusTexture });

		menu->add(MenuScene::BATTLE, mainBattle);
	}


	//		Main Battle Options
	{
		Overlay mainBattleOptions(menu->getRenderer());
		mainBattleOptions.setText("What would you like to do\n1) Fight  2) Pokemon\n3) Items  4) Flee\n");

		Button* fightButton = new Button;
		Button* pokemonButton = new Button;
		Button* itemButton = new Button;
		Button* fleeButton = new Button;

		TextBox* topLine = new TextBox;
		TextBox* bottomLine = new TextBox;

		fightButton->data = SimulationType::ATTACK_SELECTED;
		pokemonButton->data = SimulationType::POKEMON_SELECTED;
		itemButton->data = SimulationType::ITEM_SELECTED;
		fleeButton->data = SimulationType::FLEE_SELECTED;


		fightButton->text = "FIGHT";
		pokemonButton->text = "POKEMON";
		itemButton->text = "ITEM";
		fleeButton->text = "FLEE";

		topLine->text = "What should";
		bottomLine->dynamic_text = &battleData->botLine;

		fightButton->right = itemButton;
		fightButton->down = pokemonButton;
		fightButton->overlay = MenuOverlay::ATTACK_SELECT;

		pokemonButton->up = fightButton;
		pokemonButton->right = fleeButton;
		pokemonButton->scene = MenuScene::BATTLE_ROSTER;

		itemButton->left = fightButton;
		itemButton->down = fleeButton;
		itemButton->scene = MenuScene::BATTLE_ITEMS;

		fleeButton->up = itemButton;
		fleeButton->left = pokemonButton;

		fightButton->renderData = ButtonRenderData{ 63.5f,	17.75f, 19.0f, 6.5f, Color::RED };
		pokemonButton->renderData = ButtonRenderData{ 63.5f,	7.25f,	19.0f, 6.5f, Color::RED };
		itemButton->renderData = ButtonRenderData{ 86.5f,	17.75f, 19.0f, 6.5f, Color::RED };	//TODO: Find Better button colors
		fleeButton->renderData = ButtonRenderData{ 86.5f,	7.25f,	19.0f, 6.5f, Color::RED };	//TODO: Find Better button colors

		topLine->renderData = TextBoxRenderData{ 4.0f, 12.0f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		bottomLine->renderData = TextBoxRenderData{ 4.0f, 4.0f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };

		mainBattleOptions.addButton(fightButton);
		mainBattleOptions.addButton(pokemonButton);
		mainBattleOptions.addButton(itemButton);
		mainBattleOptions.addButton(fleeButton);

		mainBattleOptions.setOverlayBackground(new ImageRenderData{ 25.5f, 12.5f, 24.0f, 10.0f, g_overlayTextureLocations[MenuOverlay::BATTLE_CHAT] });

		mainBattleOptions.addTextBox(topLine);
		mainBattleOptions.addTextBox(bottomLine);

		menu->add(MenuOverlay::BATTLE_OPTIONS, mainBattleOptions);
	}

	//		Fight Screen
	{
		Overlay fightScreen(menu->getRenderer());
		fightScreen.setText("");

		Button* move1 = new Button;
		Button* move2 = new Button;
		Button* move3 = new Button;
		Button* move4 = new Button;

		move1->data = 0;
		move2->data = 1;
		move3->data = 2;
		move4->data = 3;

		move1->dynamic_text = &moves->string1;
		move2->dynamic_text = &moves->string2;
		move3->dynamic_text = &moves->string3;
		move4->dynamic_text = &moves->string4;

		move1->right = move2;
		move1->down = move3;

		move2->left = move1;
		move2->down = move4;

		move3->up = move1;
		move3->right = move4;

		move4->up = move2;
		move4->left = move3;

		move1->renderData = ButtonRenderData{ 25.0f, 18.0f, 40.0f, 8.0f, Color::RED };
		move2->renderData = ButtonRenderData{ 75.0f, 18.0f, 40.0f, 8.0f, Color::RED };
		move3->renderData = ButtonRenderData{ 25.0f,  7.0f, 40.0f, 8.0f, Color::RED };
		move4->renderData = ButtonRenderData{ 75.0f,  7.0f, 40.0f, 8.0f, Color::RED };

		fightScreen.addButton(move1);
		fightScreen.addButton(move2);
		fightScreen.addButton(move3);
		fightScreen.addButton(move4);

		menu->add(MenuOverlay::ATTACK_SELECT, fightScreen);
	}

	//	Battle Item Screen
	{
		Scene battleItemScreen(menu->getRenderer());
		battleItemScreen.setBackgroundPath(g_sceneTextureLocations[MenuScene::BATTLE_ITEMS]);
		battleItemScreen.setReturnOverlay(MenuOverlay::BATTLE_OPTIONS);

		Button* upArrow = new Button;
		Button* item1 = new Button;
		Button* item2 = new Button;
		Button* item3 = new Button;
		Button* item4 = new Button;
		Button* item5 = new Button;
		Button* downArrow = new Button;

		TextBox* item1Name = new TextBox;
		TextBox* item2Name = new TextBox;
		TextBox* item3Name = new TextBox;
		TextBox* item4Name = new TextBox;
		TextBox* item5Name = new TextBox;

		TextBox* item1Amount = new TextBox;
		TextBox* item2Amount = new TextBox;
		TextBox* item3Amount = new TextBox;
		TextBox* item4Amount = new TextBox;
		TextBox* item5Amount = new TextBox;

		upArrow->data = arrowDirections::UP;
		downArrow->data = arrowDirections::DOWN;

		item1->data = 0;
		item2->data = 1;
		item3->data = 2;
		item4->data = 3;
		item5->data = 4;

		item1->scene = MenuScene::BATTLE_ROSTER;
		item2->scene = MenuScene::BATTLE_ROSTER;
		item3->scene = MenuScene::BATTLE_ROSTER;
		item4->scene = MenuScene::BATTLE_ROSTER;
		item5->scene = MenuScene::BATTLE_ROSTER;


		upArrow->text = "UP";
		item1Name->dynamic_text = &battleItemData->itemName.string1;
		item2Name->dynamic_text = &battleItemData->itemName.string2;
		item3Name->dynamic_text = &battleItemData->itemName.string3;
		item4Name->dynamic_text = &battleItemData->itemName.string4;
		item5Name->dynamic_text = &battleItemData->itemName.string5;
		downArrow->text = "DOWN";

		item1Amount->dynamic_text = &battleItemData->itemAmount.string1;
		item2Amount->dynamic_text = &battleItemData->itemAmount.string2;
		item3Amount->dynamic_text = &battleItemData->itemAmount.string3;
		item4Amount->dynamic_text = &battleItemData->itemAmount.string4;
		item5Amount->dynamic_text = &battleItemData->itemAmount.string5;


		upArrow->up = downArrow;
		upArrow->down = item1;

		item1->up = upArrow;
		item1->down = item2;

		item2->up = item1;
		item2->down = item3;

		item3->up = item2;
		item3->down = item4;

		item4->up = item3;
		item4->down = item5;

		item5->up = item4;
		item5->down = downArrow;

		downArrow->up = item5;
		downArrow->down = upArrow;

		float topX = 50.0f;
		float topY = 90.0f;

		float buttonGap = 13.0f;

		float width = 30.0f;
		float height = 10.0f;

		Color color = Color::BUTTER_SCOTCH;

		upArrow->renderData = ButtonRenderData{ topX, topY - (buttonGap * 0), width, height, color };
		item1->renderData = ButtonRenderData{ topX, topY - (buttonGap * 1), width, height, color };
		item2->renderData = ButtonRenderData{ topX, topY - (buttonGap * 2), width, height, color };
		item3->renderData = ButtonRenderData{ topX, topY - (buttonGap * 3), width, height, color };
		item4->renderData = ButtonRenderData{ topX, topY - (buttonGap * 4), width, height, color };
		item5->renderData = ButtonRenderData{ topX, topY - (buttonGap * 5), width, height, color };
		downArrow->renderData = ButtonRenderData{ topX, topY - (buttonGap * 6), width, height, color };

		float pixels = 20.0f;
		float innerOffset = 2.0f;

		//Images are what causes things to slow
		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 1), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });
		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 2), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });
		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 3), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });
		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 4), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });
		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 5), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });

		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 1), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &battleItemData->itemTexture.string1, nullptr });
		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 2), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &battleItemData->itemTexture.string2, nullptr });
		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 3), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &battleItemData->itemTexture.string3, nullptr });
		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 4), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &battleItemData->itemTexture.string4, nullptr });
		battleItemScreen.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 5), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &battleItemData->itemTexture.string5, nullptr });

		item1Name->renderData = TextBoxRenderData{ topX - 9.0f, topY - (buttonGap * 1) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		item2Name->renderData = TextBoxRenderData{ topX - 9.0f, topY - (buttonGap * 2) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		item3Name->renderData = TextBoxRenderData{ topX - 9.0f, topY - (buttonGap * 3) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		item4Name->renderData = TextBoxRenderData{ topX - 9.0f, topY - (buttonGap * 4) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		item5Name->renderData = TextBoxRenderData{ topX - 9.0f, topY - (buttonGap * 5) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };

		item1Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 1) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		item2Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 2) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		item3Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 3) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		item4Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 4) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		item5Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 5) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };


		battleItemScreen.addTextBox(item1Name);
		battleItemScreen.addTextBox(item2Name);
		battleItemScreen.addTextBox(item3Name);
		battleItemScreen.addTextBox(item4Name);
		battleItemScreen.addTextBox(item5Name);

		battleItemScreen.addTextBox(item1Amount);
		battleItemScreen.addTextBox(item2Amount);
		battleItemScreen.addTextBox(item3Amount);
		battleItemScreen.addTextBox(item4Amount);
		battleItemScreen.addTextBox(item5Amount);

		battleItemScreen.addButton(upArrow);
		battleItemScreen.addButton(item1);
		battleItemScreen.addButton(item2);
		battleItemScreen.addButton(item3);
		battleItemScreen.addButton(item4);
		battleItemScreen.addButton(item5);
		battleItemScreen.addButton(downArrow);

		menu->add(MenuScene::BATTLE_ITEMS, battleItemScreen);
	}

	// Level Up Stats
	{
		Overlay levelUpStats{ menu->getRenderer() };
		levelUpStats.setOverlayBackground(new ImageRenderData{ 75.0f, 30.0f, 20.0f, 30.0f, g_overlayTextureLocations[MenuOverlay::LEVEL_UP_STAT_CHANGE] });

		TextBox* name = new TextBox();
		TextBox* level = new TextBox();
		TextBox* maxHP = new TextBox();
		TextBox* attack = new TextBox();
		TextBox* defense = new TextBox();
		TextBox* spAttack = new TextBox();
		TextBox* spDefense = new TextBox();
		TextBox* speed = new TextBox();

		name->dynamic_text = &battleData->pokemonStatName;
		level->dynamic_text = &battleData->pokemonStatLevel;

		maxHP->text = "MAX HP";
		attack->text = "ATTACK";
		defense->text = "DEFENSE";
		spAttack->text = "SP ATK";
		spDefense->text = "SP DEF";
		speed->text = "SPEED";


		name->renderData = TextBoxRenderData{ 75.0f, 47.0f, 5.0f };
		level->renderData = TextBoxRenderData{ 93.0f, 53.0f, 2.5f, Color::BLACK, Alignment::RIGHT_ALIGN };

		float xPos = 58.0f;
		float yPos = 38.0f;

		float yGap = 7.0f;
		float fontSize = 4.0f;

		Color textColor = Color::BLACK;

		Alignment textPosition = Alignment::LEFT_ALIGN;

		maxHP->renderData = TextBoxRenderData{ xPos, yPos - (0 * yGap), fontSize, textColor, textPosition };
		attack->renderData = TextBoxRenderData{ xPos, yPos - (1 * yGap), fontSize, textColor, textPosition };
		defense->renderData = TextBoxRenderData{ xPos, yPos - (2 * yGap), fontSize, textColor, textPosition };
		spAttack->renderData = TextBoxRenderData{ xPos, yPos - (3 * yGap), fontSize, textColor, textPosition };
		spDefense->renderData = TextBoxRenderData{ xPos, yPos - (4 * yGap), fontSize, textColor, textPosition };
		speed->renderData = TextBoxRenderData{ xPos, yPos - (5 * yGap), fontSize, textColor, textPosition };

		levelUpStats.addTextBox(name);
		levelUpStats.addTextBox(level);
		levelUpStats.addTextBox(maxHP);
		levelUpStats.addTextBox(attack);
		levelUpStats.addTextBox(defense);
		levelUpStats.addTextBox(spAttack);
		levelUpStats.addTextBox(spDefense);
		levelUpStats.addTextBox(speed);

		menu->add(MenuOverlay::LEVEL_UP_STAT_CHANGE, levelUpStats);
		menu->add(MenuOverlay::LEVEL_UP_STAT_VALUE, levelUpStats);

		// Stat Value Difference
		{
			TextBox* maxHPDiff = new TextBox();
			TextBox* attackDiff = new TextBox();
			TextBox* defenseDiff = new TextBox();
			TextBox* spAttackDiff = new TextBox();
			TextBox* spDefenseDiff = new TextBox();
			TextBox* speedDiff = new TextBox();

			maxHPDiff->dynamic_text = &battleData->pokemonStatDifference.string1;
			attackDiff->dynamic_text = &battleData->pokemonStatDifference.string2;
			defenseDiff->dynamic_text = &battleData->pokemonStatDifference.string3;
			spAttackDiff->dynamic_text = &battleData->pokemonStatDifference.string4;
			spDefenseDiff->dynamic_text = &battleData->pokemonStatDifference.string5;
			speedDiff->dynamic_text = &battleData->pokemonStatDifference.string6;

			maxHPDiff->renderData = TextBoxRenderData{ 93.0f, yPos - (0 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			attackDiff->renderData = TextBoxRenderData{ 93.0f, yPos - (1 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			defenseDiff->renderData = TextBoxRenderData{ 93.0f, yPos - (2 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			spAttackDiff->renderData = TextBoxRenderData{ 93.0f, yPos - (3 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			spDefenseDiff->renderData = TextBoxRenderData{ 93.0f, yPos - (4 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			speedDiff->renderData = TextBoxRenderData{ 93.0f, yPos - (5 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };

			menu->modify(MenuOverlay::LEVEL_UP_STAT_CHANGE)->addTextBox(maxHPDiff);
			menu->modify(MenuOverlay::LEVEL_UP_STAT_CHANGE)->addTextBox(attackDiff);
			menu->modify(MenuOverlay::LEVEL_UP_STAT_CHANGE)->addTextBox(defenseDiff);
			menu->modify(MenuOverlay::LEVEL_UP_STAT_CHANGE)->addTextBox(spAttackDiff);
			menu->modify(MenuOverlay::LEVEL_UP_STAT_CHANGE)->addTextBox(spDefenseDiff);
			menu->modify(MenuOverlay::LEVEL_UP_STAT_CHANGE)->addTextBox(speedDiff);
		}

		// New Stat Values
		{
			TextBox* maxHPValue = new TextBox();
			TextBox* attackValue = new TextBox();
			TextBox* defenseValue = new TextBox();
			TextBox* spAttackValue = new TextBox();
			TextBox* spDefenseValue = new TextBox();
			TextBox* speedValue = new TextBox();

			maxHPValue->dynamic_text = &battleData->pokemonStatValue.string1;
			attackValue->dynamic_text = &battleData->pokemonStatValue.string2;
			defenseValue->dynamic_text = &battleData->pokemonStatValue.string3;
			spAttackValue->dynamic_text = &battleData->pokemonStatValue.string4;
			spDefenseValue->dynamic_text = &battleData->pokemonStatValue.string5;
			speedValue->dynamic_text = &battleData->pokemonStatValue.string6;

			maxHPValue->renderData = TextBoxRenderData{ 93.0f, yPos - (0 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			attackValue->renderData = TextBoxRenderData{ 93.0f, yPos - (1 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			defenseValue->renderData = TextBoxRenderData{ 93.0f, yPos - (2 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			spAttackValue->renderData = TextBoxRenderData{ 93.0f, yPos - (3 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			spDefenseValue->renderData = TextBoxRenderData{ 93.0f, yPos - (4 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };
			speedValue->renderData = TextBoxRenderData{ 93.0f, yPos - (5 * yGap), fontSize, textColor, Alignment::RIGHT_ALIGN };


			menu->modify(MenuOverlay::LEVEL_UP_STAT_VALUE)->addTextBox(maxHPValue);
			menu->modify(MenuOverlay::LEVEL_UP_STAT_VALUE)->addTextBox(attackValue);
			menu->modify(MenuOverlay::LEVEL_UP_STAT_VALUE)->addTextBox(defenseValue);
			menu->modify(MenuOverlay::LEVEL_UP_STAT_VALUE)->addTextBox(spAttackValue);
			menu->modify(MenuOverlay::LEVEL_UP_STAT_VALUE)->addTextBox(spDefenseValue);
			menu->modify(MenuOverlay::LEVEL_UP_STAT_VALUE)->addTextBox(speedValue);
		}
	}

	// Swap Pokemon From Opponent Faint
	{
		Overlay wouldLikeToSwapPokemon{ menu->getRenderer()};

		Button* swapPokemon = new Button;
		Button* keepBattling = new Button;

		swapPokemon->data = (int)true;
		keepBattling->data = (int)false;

		swapPokemon->text = "Swap Pokemon";
		keepBattling->text = "Keep Battling";

		swapPokemon->up = keepBattling;
		swapPokemon->down = keepBattling;

		keepBattling->up = swapPokemon;
		keepBattling->down = swapPokemon;

		swapPokemon->renderData = ButtonRenderData{ 50.0f,	17.75f, 20.0f, 6.5f, Color::WHITE };
		keepBattling->renderData = ButtonRenderData{ 50.0f,	7.25f, 20.0f, 6.5f, Color::WHITE };

		wouldLikeToSwapPokemon.addButton(swapPokemon);
		wouldLikeToSwapPokemon.addButton(keepBattling);

		menu->add(MenuOverlay::SWAP_POKEMON_QUESTION, wouldLikeToSwapPokemon);
	}

	// Learn Move Yes NO
	{
		Overlay learnNewMove{ menu->getRenderer() };

		Button* learnMove = new Button;
		Button* forgetMove = new Button;

		learnMove->data = (int)true;
		forgetMove->data = (int)false;

		learnMove->text = "Learn Move";
		forgetMove->text = "Dont Learn";

		learnMove->up = forgetMove;
		learnMove->down = forgetMove;

		forgetMove->up = learnMove;
		forgetMove->down = learnMove;

		learnMove->renderData = ButtonRenderData{ 50.0f,	17.75f, 20.0f, 6.5f, Color::WHITE };
		forgetMove->renderData = ButtonRenderData{ 50.0f,	7.25f, 20.0f, 6.5f, Color::WHITE };

		learnNewMove.addButton(learnMove);
		learnNewMove.addButton(forgetMove);

		menu->add(MenuOverlay::LEARN_MOVE, learnNewMove);
	}

	// Learn a new Move 
	{
		Scene learnNewMove{ menu->getRenderer() };
		learnNewMove.setBackgroundPath(g_sceneTextureLocations[MenuScene::LEARN_MOVE]);

		// Moves
		{
			// Buttons
			{
				Button* move1Button = new Button();
				Button* move2Button = new Button();
				Button* move3Button = new Button();
				Button* move4Button = new Button();
				Button* newMoveButton = new Button();

				move1Button->data = 0;
				move2Button->data = 1;
				move3Button->data = 2;
				move4Button->data = 3;
				newMoveButton->data = 4;

				move1Button->up = move4Button;
				move1Button->down = move2Button;
				move1Button->left = newMoveButton;

				move2Button->up = move1Button;
				move2Button->down = move3Button;
				move2Button->left = newMoveButton;

				move3Button->up = move2Button;
				move3Button->down = move4Button;
				move3Button->left = newMoveButton;

				move4Button->up = move3Button;
				move4Button->down = move1Button;
				move4Button->left = newMoveButton;

				newMoveButton->right = move1Button;

				move1Button->renderData = ButtonRenderData{ 0,0,0,0, Color::TRANSPARENT, 0,&learnMoveData->buttonVisibility };
				move2Button->renderData = ButtonRenderData{ 0,0,0,0, Color::TRANSPARENT, 0,&learnMoveData->buttonVisibility };
				move3Button->renderData = ButtonRenderData{ 0,0,0,0, Color::TRANSPARENT, 0,&learnMoveData->buttonVisibility };
				move4Button->renderData = ButtonRenderData{ 0,0,0,0, Color::TRANSPARENT, 0,&learnMoveData->buttonVisibility };
				newMoveButton->renderData = ButtonRenderData{ 0,0,0,0, Color::TRANSPARENT, 0,&learnMoveData->buttonVisibility };

				learnNewMove.addButton(move1Button);
				learnNewMove.addButton(move2Button);
				learnNewMove.addButton(move3Button);
				learnNewMove.addButton(move4Button);
				learnNewMove.addButton(newMoveButton);
			}

			// Move Data
			{
				TextBox* moveText = new TextBox();
				moveText->text = "MOVES";
				moveText->renderData = TextBoxRenderData{ 84.0f, (473.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK };
				learnNewMove.addTextBox(moveText);

				TextBox* move1Name = new TextBox();
				TextBox* move2Name = new TextBox();
				TextBox* move3Name = new TextBox();
				TextBox* move4Name = new TextBox();
				TextBox* newMoveName = new TextBox();

				TextBox* currentPP1 = new TextBox();
				TextBox* currentPP2 = new TextBox();
				TextBox* currentPP3 = new TextBox();
				TextBox* currentPP4 = new TextBox();
				TextBox* newMovePP = new TextBox();

				TextBox* maxPP1 = new TextBox();
				TextBox* maxPP2 = new TextBox();
				TextBox* maxPP3 = new TextBox();
				TextBox* maxPP4 = new TextBox();
				TextBox* newMoveMaxPP = new TextBox();

				move1Name->dynamic_text = &learnMoveData->move1.moveName;
				move2Name->dynamic_text = &learnMoveData->move2.moveName;
				move3Name->dynamic_text = &learnMoveData->move3.moveName;
				move4Name->dynamic_text = &learnMoveData->move4.moveName;
				newMoveName->dynamic_text = &learnMoveData->newMove.moveName;

				currentPP1->dynamic_text = &learnMoveData->move1.currentPP;
				currentPP2->dynamic_text = &learnMoveData->move2.currentPP;
				currentPP3->dynamic_text = &learnMoveData->move3.currentPP;
				currentPP4->dynamic_text = &learnMoveData->move4.currentPP;
				newMovePP->dynamic_text = &learnMoveData->newMove.currentPP;

				maxPP1->dynamic_text = &learnMoveData->move1.maxPP;
				maxPP2->dynamic_text = &learnMoveData->move2.maxPP;
				maxPP3->dynamic_text = &learnMoveData->move3.maxPP;
				maxPP4->dynamic_text = &learnMoveData->move4.maxPP;
				newMoveMaxPP->dynamic_text = &learnMoveData->newMove.maxPP;

				move1Name->renderData = TextBoxRenderData{ 74.0f, (373.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
				move2Name->renderData = TextBoxRenderData{ 74.0f, (283.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
				move3Name->renderData = TextBoxRenderData{ 74.0f, (193.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
				move4Name->renderData = TextBoxRenderData{ 74.0f, (103.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
				newMoveName->renderData = TextBoxRenderData{ 6.6f, (373.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };

				currentPP1->renderData = TextBoxRenderData{ (875.0f / 1000.0f) * 100.0f, (330.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
				currentPP2->renderData = TextBoxRenderData{ (875.0f / 1000.0f) * 100.0f, (240.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
				currentPP3->renderData = TextBoxRenderData{ (875.0f / 1000.0f) * 100.0f, (150.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
				currentPP4->renderData = TextBoxRenderData{ (875.0f / 1000.0f) * 100.0f, (60.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
				newMovePP->renderData = TextBoxRenderData{ (201.0f / 1000.0f) * 100.0f, (330.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };

				maxPP1->renderData = TextBoxRenderData{ (890.0f / 1000.0f) * 100.0f, (330.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
				maxPP2->renderData = TextBoxRenderData{ (890.0f / 1000.0f) * 100.0f, (240.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
				maxPP3->renderData = TextBoxRenderData{ (890.0f / 1000.0f) * 100.0f, (150.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
				maxPP4->renderData = TextBoxRenderData{ (890.0f / 1000.0f) * 100.0f, (60.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
				newMoveMaxPP->renderData = TextBoxRenderData{ (216.0f / 1000.0f) * 100.0f, (330.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };

				learnNewMove.addTextBox(move1Name);
				learnNewMove.addTextBox(move2Name);
				learnNewMove.addTextBox(move3Name);
				learnNewMove.addTextBox(move4Name);
				learnNewMove.addTextBox(newMoveName);

				learnNewMove.addTextBox(currentPP1);
				learnNewMove.addTextBox(currentPP2);
				learnNewMove.addTextBox(currentPP3);
				learnNewMove.addTextBox(currentPP4);
				learnNewMove.addTextBox(newMovePP);

				learnNewMove.addTextBox(maxPP1);
				learnNewMove.addTextBox(maxPP2);
				learnNewMove.addTextBox(maxPP3);
				learnNewMove.addTextBox(maxPP4);
				learnNewMove.addTextBox(newMoveMaxPP);

				learnNewMove.addImage(new ImageRenderData{ 77.0f, (353.0f / 563.0f) * 100.0f, 3.0f, 1.5f, " " ,&learnMoveData->move1.moveTypeTextureLocation });
				learnNewMove.addImage(new ImageRenderData{ 77.0f, (263.0f / 563.0f) * 100.0f, 3.0f, 1.5f, " " ,&learnMoveData->move2.moveTypeTextureLocation });
				learnNewMove.addImage(new ImageRenderData{ 77.0f, (173.0f / 563.0f) * 100.0f, 3.0f, 1.5f, " " ,&learnMoveData->move3.moveTypeTextureLocation });
				learnNewMove.addImage(new ImageRenderData{ 77.0f, (083.0f / 563.0f) * 100.0f, 3.0f, 1.5f, " " ,&learnMoveData->move4.moveTypeTextureLocation });
				learnNewMove.addImage(new ImageRenderData{ 09.2f, (353.0f / 563.0f) * 100.0f, 3.0f, 1.5f, " " ,&learnMoveData->newMove.moveTypeTextureLocation });
			}

			//	Highlighted Move Data
			{
				TextBox* power = new TextBox();
				TextBox* accuracy = new TextBox();
				TextBox* description = new TextBox();

				power->dynamic_text = &learnMoveData->power;
				accuracy->dynamic_text = &learnMoveData->accuracy;
				description->dynamic_text = &learnMoveData->description;

				power->renderData = TextBoxRenderData{ 50.0f, (411.0f / 563.0f) * 100.0f, 4.0f };
				accuracy->renderData = TextBoxRenderData{ 50.0f, (334.0f / 563.0f) * 100.0f, 4.0f };
				description->renderData = TextBoxRenderData{ 37.8f, (230.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };

				learnNewMove.addTextBox(power);
				learnNewMove.addTextBox(accuracy);
				learnNewMove.addTextBox(description);
			}

			// Move Highlight Images
			{
				//Width  = 226 px
				//Height =  98 px

				float leftAdjustment = 1.6f;
				float downAdjustment = 0.7f;

				float xPercent = ((835.5f - leftAdjustment) / 1000.0f) * 100.0f;
				float newMovexPercent = ((161.5f - leftAdjustment) / 1000.0f) * 100.0f;

				learnNewMove.addImage(new ImageRenderData{ xPercent,		((367.5f - downAdjustment) / 563.0f) * 100.0f,  (113.0f / 1000.0f) * 100.0f, (50.0f / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::MOVE_OUTLINE], nullptr, &learnMoveData->move1OutlineVisiblity });	//Move 1
				learnNewMove.addImage(new ImageRenderData{ xPercent,		((278.5f - downAdjustment) / 563.0f) * 100.0f,  (113.0f / 1000.0f) * 100.0f, (50.0f / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::MOVE_OUTLINE], nullptr, &learnMoveData->move2OutlineVisiblity });	//Move 2
				learnNewMove.addImage(new ImageRenderData{ xPercent,		((188.5f - downAdjustment) / 563.0f) * 100.0f,  (113.0f / 1000.0f) * 100.0f, (50.0f / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::MOVE_OUTLINE], nullptr, &learnMoveData->move3OutlineVisiblity });	//Move 3
				learnNewMove.addImage(new ImageRenderData{ xPercent,		((98.5f - downAdjustment) / 563.0f) * 100.0f,  (113.0f / 1000.0f) * 100.0f, (50.0f / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::MOVE_OUTLINE], nullptr, &learnMoveData->move4OutlineVisiblity });		//Move 4
				learnNewMove.addImage(new ImageRenderData{ newMovexPercent, ((367.5f - downAdjustment) / 563.0f) * 100.0f,  (113.0f / 1000.0f) * 100.0f, (50.0f / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::MOVE_OUTLINE], nullptr, &learnMoveData->newMoveOutlineVisiblity });	//New Move
			}
		}

		// Pokemon
		{
			TextBox* pokemonName = new TextBox();
			pokemonName->dynamic_text = &learnMoveData->pokemonName;
			pokemonName->renderData = TextBoxRenderData{ 15.0f, (210.0f / 563.0f) * 100.0f, 4.0f };

			float pokemonSizeReduction = 1.3;	//Always Greater than 1

			learnNewMove.addTextBox(pokemonName);
			learnNewMove.addImage(new ImageRenderData{ 15.0f, (189.0f / 563.0f) * 100.0f, 5.0f, 2.5f, "", &learnMoveData->pokemonType1TextureLocation });
			learnNewMove.addImage(new ImageRenderData{ 25.0f, (189.0f / 563.0f) * 100.0f, 5.0f, 2.5f, "", &learnMoveData->pokemonType2TextureLocation });
			learnNewMove.addImage(new ImageRenderData{ 15.0f, (94.5f / 563.0f) * 100.0f, 9.0f / pokemonSizeReduction, 16.0f / pokemonSizeReduction, "", &learnMoveData->pokemonImageTextureLocation });
		}

		menu->add(MenuScene::LEARN_MOVE, learnNewMove);
	}

	// Evolution
	{
		Scene evolution{ menu->getRenderer() };
		evolution.setBackgroundPath(g_sceneTextureLocations[MenuScene::EVOLUTION]);
		evolution.addDynamicImage(playerPokemon);
		evolution.addDynamicImage(oppPokemon);
		menu->add(MenuScene::EVOLUTION, evolution);

	}
}

void MenuSetup::setupInteractionData(Menu* menu, SharedString* items, std::string* balance, NurseHealData* nurseHealData)
{
	// Nurse Heal
	{
		Overlay nurseHeal(menu->getRenderer());

		float x = (297.0f / 1000.0f) * 100.0f;
		float y = (495.0f / 563.0f) * 100.0f;

		float xGap = 4.9f;
		float yGap = 7.5f;

		float scale = 5.0f;

		float width = 9.0f / scale;
		float height = 16.0f / scale;

		//Top Row
		nurseHeal.addImage(new ImageRenderData{ x + (xGap * 0), y - (yGap * 0), width, height, "", &nurseHealData->textures.string1, &nurseHealData->visibility.bool1 });
		nurseHeal.addImage(new ImageRenderData{ x + (xGap * 1), y - (yGap * 0), width, height, "", &nurseHealData->textures.string2, &nurseHealData->visibility.bool2 });
		nurseHeal.addImage(new ImageRenderData{ x + (xGap * 2), y - (yGap * 0), width, height, "", &nurseHealData->textures.string3, &nurseHealData->visibility.bool3 });

		//Bottom Row
		nurseHeal.addImage(new ImageRenderData{ x + (xGap * 0), y - (yGap * 1), width, height, "", &nurseHealData->textures.string4, &nurseHealData->visibility.bool4 });
		nurseHeal.addImage(new ImageRenderData{ x + (xGap * 1), y - (yGap * 1), width, height, "", &nurseHealData->textures.string5, &nurseHealData->visibility.bool5 });
		nurseHeal.addImage(new ImageRenderData{ x + (xGap * 2), y - (yGap * 1), width, height, "", &nurseHealData->textures.string6, &nurseHealData->visibility.bool6 });

		menu->add(MenuOverlay::NURSE_POKEBALL, nurseHeal);
	}
}

void MenuSetup::setupPauseData(Menu* menu, ItemDisplayData* items, PauseMenuData* pauseMenuData, RosterDisplayData* rosterData, PauseSettingsData* settingData)
{
	// Pause Main Menu
	{
		Scene pauseMainMenu(menu->getRenderer());
		pauseMainMenu.setBackgroundPath(g_sceneTextureLocations[MenuScene::PAUSE_MENU]);

		TextBox* playerBalance = new TextBox();
		playerBalance->dynamic_text = &pauseMenuData->playerBalance;
		playerBalance->renderData = TextBoxRenderData{ 3.0f, 74.4f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };

		TextBox* playTime = new TextBox();
		playTime->dynamic_text = &pauseMenuData->playTime;
		playTime->renderData = TextBoxRenderData{ 98.0f, 74.4f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };

		pauseMainMenu.addTextBox(playerBalance);
		pauseMainMenu.addTextBox(playTime);

		// Option Buttons
		{
			Button* pokemonRoster = new Button;
			Button* bagOfItems = new Button;
			Button* mapView = new Button;
			Button* pokedex = new Button;
			Button* changeSettings = new Button;
			Button* saveGame = new Button;
			Button* exitGame = new Button;

			//TODO: Probably dont hard code these but also i dont care
			pokemonRoster->data = 0;
			mapView->data = 2;
			bagOfItems->data = 1;
			changeSettings->data = 3;
			saveGame->data = 4;
			exitGame->data = 5;
			pokedex->data = 6;


			pokemonRoster->down = saveGame;
			pokemonRoster->left = pokedex;
			pokemonRoster->right = bagOfItems;

			bagOfItems->down = changeSettings;
			bagOfItems->left = pokemonRoster;
			bagOfItems->right = mapView;

			pokedex->down = exitGame;
			pokedex->goBackOnRight = true;

			mapView->down = exitGame;
			mapView->goBackOnLeft = true;

			saveGame->up = pokemonRoster;
			saveGame->down = exitGame;
			saveGame->left = pokedex;
			saveGame->right = changeSettings;

			changeSettings->up = bagOfItems;
			changeSettings->down = exitGame;
			changeSettings->left = saveGame;
			changeSettings->right = mapView;

			exitGame->up = saveGame;
			exitGame->left = pokedex;
			exitGame->right = mapView;

			pokemonRoster->text = "ROSTER";
			bagOfItems->text = "BAG";
			changeSettings->text = "SETTINGS";
			saveGame->text = "SAVE";
			exitGame->text = "EXIT";

			float xPos = 37.5f;
			float yPos = 60.0f;
			float widthPercent = 18.75;
			float heightPercent = 13.5;

			float yGap = 20.0f;
			float xGap = 25.0f;

			pokemonRoster->renderData = { xPos, yPos, widthPercent, heightPercent, Color::BLUE };
			saveGame->renderData = { xPos, yPos - yGap, widthPercent, heightPercent, Color::BLUE };

			bagOfItems->renderData = { xPos + xGap, yPos, widthPercent, heightPercent, Color::BLUE };
			changeSettings->renderData = { xPos + xGap, yPos - yGap,	widthPercent, heightPercent, Color::BLUE };

			exitGame->renderData = { xPos + (xGap / 2.0f), yPos - (yGap * 2.0f), widthPercent, heightPercent, Color::BLUE };

			pokedex->active = &pauseMenuData->pokedexButtonUsable;
			mapView->active = &pauseMenuData->mapButtonUsable;

			pokedex->renderData = { 0.0f, 0.0f,	0.0f, 0.0f, Color::TRANSPARENT, renderOptions::autoSizeText, &pauseMenuData->buttonVisibility };
			mapView->renderData = { 0.0f, 0.0f,	0.0f, 0.0f, Color::TRANSPARENT, renderOptions::autoSizeText, &pauseMenuData->buttonVisibility };

			pokemonRoster->scene = MenuScene::PAUSE_ROSTER;
			changeSettings->scene = MenuScene::PAUSE_SETTINGS;
			bagOfItems->scene = MenuScene::PAUSE_BAG;
			pokedex->scene = MenuScene::POKEDEX;

			pauseMainMenu.addButton(pokemonRoster);
			pauseMainMenu.addButton(pokedex);
			pauseMainMenu.addButton(mapView);
			pauseMainMenu.addButton(bagOfItems);
			pauseMainMenu.addButton(changeSettings);
			pauseMainMenu.addButton(saveGame);
			pauseMainMenu.addButton(exitGame);


			float pokedexXPercent = (124.5f / 1000.0f) * 100.0f;
			float pokedexYPercent = (246.0f / 563.0f) * 100.0f;

			float mapXPercent = (874.5f / 1000.0f) * 100.0f;
			float mapYPercent = (246.0f / 563.0f) * 100.0f;

			float imageWidthPercent = ((123.0f / 1000.0f) * 100.0f) / 2.0f;
			float imageHeightPercent = ((252.0f / 563.0f) * 100.0f) / 2.0f;

			pauseMainMenu.addImage(new ImageRenderData{ pokedexXPercent, pokedexYPercent, imageWidthPercent, imageHeightPercent, g_overlayTextureLocations[MenuOverlay::PAUSE_POKEDEX_IMAGE], nullptr, &pauseMenuData->pokedexButtonUsable });
			pauseMainMenu.addImage(new ImageRenderData{ mapXPercent, mapYPercent, imageWidthPercent, imageHeightPercent, g_overlayTextureLocations[MenuOverlay::PAUSE_MAP_IMAGE], nullptr, &pauseMenuData->mapButtonUsable });

			pauseMainMenu.addImage(new ImageRenderData{ pokedexXPercent, pokedexYPercent, imageWidthPercent, imageHeightPercent, g_overlayTextureLocations[MenuOverlay::POKEDEX_OUTLINE], nullptr, &pauseMenuData->pokedexHighlightVisible });
			pauseMainMenu.addImage(new ImageRenderData{ mapXPercent, mapYPercent, imageWidthPercent, imageHeightPercent, g_overlayTextureLocations[MenuOverlay::MAP_OUTLINE], nullptr, &pauseMenuData->mapHighlightVisible });
		}

		// Badge Images
		{
			//31% 70

			pauseMainMenu.addImage(new ImageRenderData{ (309.0f / 1000.0f) * 100.0f, (493.5f / 563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/normalBadge.png",	nullptr, &pauseMenuData->badgeData.normalBadgeVisibility });
			pauseMainMenu.addImage(new ImageRenderData{ (365.0f / 1000.0f) * 100.0f, (493.5f / 563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/waterBadge.png",	nullptr, &pauseMenuData->badgeData.waterBadgeVisibility });
			pauseMainMenu.addImage(new ImageRenderData{ (421.0f / 1000.0f) * 100.0f, (493.5f / 563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/rockBadge.png",		nullptr, &pauseMenuData->badgeData.rockBadgeVisibility });
			pauseMainMenu.addImage(new ImageRenderData{ (477.0f / 1000.0f) * 100.0f, (493.5f / 563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/flyingBadge.png",	nullptr, &pauseMenuData->badgeData.flyingBadgeVisibility });
			pauseMainMenu.addImage(new ImageRenderData{ (533.0f / 1000.0f) * 100.0f, (493.5f / 563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/grassBadge.png",	nullptr, &pauseMenuData->badgeData.grassBadgeVisibility });
			pauseMainMenu.addImage(new ImageRenderData{ (589.0f / 1000.0f) * 100.0f, (493.5f / 563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/iceBadge.png",		nullptr, &pauseMenuData->badgeData.iceBadgeVisibility });
			pauseMainMenu.addImage(new ImageRenderData{ (645.0f / 1000.0f) * 100.0f, (493.5f / 563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/fireBadge.png",		nullptr, &pauseMenuData->badgeData.fireBadgeVisibility });
			pauseMainMenu.addImage(new ImageRenderData{ (701.0f / 1000.0f) * 100.0f, (493.5f / 563.0f) * 100.0f, 2.5f, 4.440497336f, "Images/Badges/dragonBadge.png",	nullptr, &pauseMenuData->badgeData.dragonBadgeVisibility });
		}

		menu->add(MenuScene::PAUSE_MENU, pauseMainMenu);
	}


	// Pause Roster Menu
	{
		Scene pauseRosterMenu(menu->getRenderer());
		pauseRosterMenu.setBackgroundPath(g_sceneTextureLocations[MenuScene::PAUSE_ROSTER]);

		Button* roster1 = new Button;
		Button* roster2 = new Button;
		Button* roster3 = new Button;
		Button* roster4 = new Button;
		Button* roster5 = new Button;
		Button* roster6 = new Button;

		roster1->data = 0;
		roster2->data = 1;
		roster3->data = 2;
		roster4->data = 3;
		roster5->data = 4;
		roster6->data = 5;


		roster1->down = roster2;

		roster2->up = roster1;
		roster2->down = roster3;

		roster3->up = roster2;
		roster3->down = roster4;

		roster4->up = roster3;
		roster4->down = roster5;

		roster5->up = roster4;
		roster5->down = roster6;

		roster6->up = roster5;

		roster1->renderData = { 50.0f, 89.5f, 33.0f, 10.8f, Color::BLUE };
		roster2->renderData = { 50.0f, 73.7f, 33.0f, 10.8f, Color::BLUE };
		roster3->renderData = { 50.0f, 57.9f, 33.0f, 10.8f, Color::BLUE };
		roster4->renderData = { 50.0f, 42.1f, 33.0f, 10.8f, Color::BLUE };
		roster5->renderData = { 50.0f, 26.3f, 33.0f, 10.8f, Color::BLUE };
		roster6->renderData = { 50.0f, 10.5f, 33.0f, 10.8f, Color::BLUE };

		pauseRosterMenu.addButton(roster1);
		pauseRosterMenu.addButton(roster2);
		pauseRosterMenu.addButton(roster3);
		pauseRosterMenu.addButton(roster4);
		pauseRosterMenu.addButton(roster5);
		pauseRosterMenu.addButton(roster6);

		TextBox* pokemonName = new TextBox();
		TextBox* pokemonLevel = new TextBox();
		TextBox* pokemonHealth = new TextBox();

		// Roster Data
		{
			TextBox* pokemon1Name = new TextBox();
			TextBox* pokemon2Name = new TextBox();
			TextBox* pokemon3Name = new TextBox();
			TextBox* pokemon4Name = new TextBox();
			TextBox* pokemon5Name = new TextBox();
			TextBox* pokemon6Name = new TextBox();

			TextBox* pokemon1level = new TextBox();
			TextBox* pokemon2level = new TextBox();
			TextBox* pokemon3level = new TextBox();
			TextBox* pokemon4level = new TextBox();
			TextBox* pokemon5level = new TextBox();
			TextBox* pokemon6level = new TextBox();

			TextBox* pokemon1hp = new TextBox();
			TextBox* pokemon2hp = new TextBox();
			TextBox* pokemon3hp = new TextBox();
			TextBox* pokemon4hp = new TextBox();
			TextBox* pokemon5hp = new TextBox();
			TextBox* pokemon6hp = new TextBox();



			pokemon1Name->dynamic_text = &rosterData->pokemon1.name;
			pokemon2Name->dynamic_text = &rosterData->pokemon2.name;
			pokemon3Name->dynamic_text = &rosterData->pokemon3.name;
			pokemon4Name->dynamic_text = &rosterData->pokemon4.name;
			pokemon5Name->dynamic_text = &rosterData->pokemon5.name;
			pokemon6Name->dynamic_text = &rosterData->pokemon6.name;

			pokemon1level->dynamic_text = &rosterData->pokemon1.level;
			pokemon2level->dynamic_text = &rosterData->pokemon2.level;
			pokemon3level->dynamic_text = &rosterData->pokemon3.level;
			pokemon4level->dynamic_text = &rosterData->pokemon4.level;
			pokemon5level->dynamic_text = &rosterData->pokemon5.level;
			pokemon6level->dynamic_text = &rosterData->pokemon6.level;

			pokemon1hp->dynamic_text = &rosterData->pokemon1.hp;
			pokemon2hp->dynamic_text = &rosterData->pokemon2.hp;
			pokemon3hp->dynamic_text = &rosterData->pokemon3.hp;
			pokemon4hp->dynamic_text = &rosterData->pokemon4.hp;
			pokemon5hp->dynamic_text = &rosterData->pokemon5.hp;
			pokemon6hp->dynamic_text = &rosterData->pokemon6.hp;

			pokemon1Name->renderData = TextBoxRenderData{ 66.0f, 89.5f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			pokemon2Name->renderData = TextBoxRenderData{ 66.0f, 73.7f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			pokemon3Name->renderData = TextBoxRenderData{ 66.0f, 57.9f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			pokemon4Name->renderData = TextBoxRenderData{ 66.0f, 42.1f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			pokemon5Name->renderData = TextBoxRenderData{ 66.0f, 26.3f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			pokemon6Name->renderData = TextBoxRenderData{ 66.0f, 10.5f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };

			pokemon1level->renderData = TextBoxRenderData{ 34.5f, 83.5f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			pokemon2level->renderData = TextBoxRenderData{ 34.5f, 67.7f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			pokemon3level->renderData = TextBoxRenderData{ 34.5f, 51.9f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			pokemon4level->renderData = TextBoxRenderData{ 34.5f, 36.1f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			pokemon5level->renderData = TextBoxRenderData{ 34.5f, 20.3f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			pokemon6level->renderData = TextBoxRenderData{ 34.5f,  4.5f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };

			pokemon1hp->renderData = TextBoxRenderData{ 66.5f, 83.5f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			pokemon2hp->renderData = TextBoxRenderData{ 66.5f, 67.7f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			pokemon3hp->renderData = TextBoxRenderData{ 66.5f, 51.9f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			pokemon4hp->renderData = TextBoxRenderData{ 66.5f, 36.1f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			pokemon5hp->renderData = TextBoxRenderData{ 66.5f, 20.3f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			pokemon6hp->renderData = TextBoxRenderData{ 66.5f,  4.5f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };

			pauseRosterMenu.addTextBox(pokemon1Name);
			pauseRosterMenu.addTextBox(pokemon2Name);
			pauseRosterMenu.addTextBox(pokemon3Name);
			pauseRosterMenu.addTextBox(pokemon4Name);
			pauseRosterMenu.addTextBox(pokemon5Name);
			pauseRosterMenu.addTextBox(pokemon6Name);

			pauseRosterMenu.addTextBox(pokemon1level);
			pauseRosterMenu.addTextBox(pokemon2level);
			pauseRosterMenu.addTextBox(pokemon3level);
			pauseRosterMenu.addTextBox(pokemon4level);
			pauseRosterMenu.addTextBox(pokemon5level);
			pauseRosterMenu.addTextBox(pokemon6level);

			pauseRosterMenu.addTextBox(pokemon1hp);
			pauseRosterMenu.addTextBox(pokemon2hp);
			pauseRosterMenu.addTextBox(pokemon3hp);
			pauseRosterMenu.addTextBox(pokemon4hp);
			pauseRosterMenu.addTextBox(pokemon5hp);
			pauseRosterMenu.addTextBox(pokemon6hp);

			float pixels = 15.0f;
			float innerOffset = 2.0f;

			float statusWidth = 2.0f;
			float statusHeight = statusWidth / 2.0f;

			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 91.5f, (pixels / 1000.0f) * 100.0f, (pixels / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 75.7f, (pixels / 1000.0f) * 100.0f, (pixels / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 59.9f, (pixels / 1000.0f) * 100.0f, (pixels / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 44.1f, (pixels / 1000.0f) * 100.0f, (pixels / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 28.3f, (pixels / 1000.0f) * 100.0f, (pixels / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 12.5f, (pixels / 1000.0f) * 100.0f, (pixels / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });

			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 91.5f, ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &rosterData->pokemon1.pokemonTexture });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 75.7f, ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &rosterData->pokemon2.pokemonTexture });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 59.9f, ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &rosterData->pokemon3.pokemonTexture });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 44.1f, ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &rosterData->pokemon4.pokemonTexture });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 28.3f, ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &rosterData->pokemon5.pokemonTexture });
			pauseRosterMenu.addImage(new ImageRenderData{ 36.0f, 12.5f, ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &rosterData->pokemon6.pokemonTexture });

			pauseRosterMenu.addImage(new ImageRenderData{ 41.0f, 91.5f, statusWidth, statusHeight, "", &rosterData->pokemon1.majorStatusTexture });
			pauseRosterMenu.addImage(new ImageRenderData{ 41.0f, 75.7f, statusWidth, statusHeight, "", &rosterData->pokemon2.majorStatusTexture });
			pauseRosterMenu.addImage(new ImageRenderData{ 41.0f, 59.9f, statusWidth, statusHeight, "", &rosterData->pokemon3.majorStatusTexture });
			pauseRosterMenu.addImage(new ImageRenderData{ 41.0f, 44.1f, statusWidth, statusHeight, "", &rosterData->pokemon4.majorStatusTexture });
			pauseRosterMenu.addImage(new ImageRenderData{ 41.0f, 28.3f, statusWidth, statusHeight, "", &rosterData->pokemon5.majorStatusTexture });
			pauseRosterMenu.addImage(new ImageRenderData{ 41.0f, 12.5f, statusWidth, statusHeight, "", &rosterData->pokemon6.majorStatusTexture });


		}

		// Static Text
		{
			TextBox* typeTextBox = new TextBox();
			TextBox* hpTextBox = new TextBox();
			TextBox* attackTextBox = new TextBox();
			TextBox* defenseTextBox = new TextBox();
			TextBox* spAttackTextBox = new TextBox();
			TextBox* spDefenseTextBox = new TextBox();
			TextBox* speedTextBox = new TextBox();


			typeTextBox->text = "Type";
			hpTextBox->text = "HP";
			attackTextBox->text = "Attack";
			defenseTextBox->text = "Defense";
			spAttackTextBox->text = "SpAttack";
			spDefenseTextBox->text = "spDefense";
			speedTextBox->text = "Speed";

			typeTextBox->renderData = TextBoxRenderData{ 1.0f,		(408.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			hpTextBox->renderData = TextBoxRenderData{ 1.0f,							 62.5f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			attackTextBox->renderData = TextBoxRenderData{ 1.0f,	(253.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			defenseTextBox->renderData = TextBoxRenderData{ 1.0f,	(213.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			spAttackTextBox->renderData = TextBoxRenderData{ 1.0f,	(173.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			spDefenseTextBox->renderData = TextBoxRenderData{ 1.0f,	(133.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			speedTextBox->renderData = TextBoxRenderData{ 1.0f,		(93.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };

			pauseRosterMenu.addTextBox(typeTextBox);
			pauseRosterMenu.addTextBox(hpTextBox);
			pauseRosterMenu.addTextBox(attackTextBox);
			pauseRosterMenu.addTextBox(defenseTextBox);
			pauseRosterMenu.addTextBox(spAttackTextBox);
			pauseRosterMenu.addTextBox(spDefenseTextBox);
			pauseRosterMenu.addTextBox(speedTextBox);
		}

		// Left Side Data
		{
			TextBox* attack = new TextBox();
			TextBox* defense = new TextBox();
			TextBox* spAttack = new TextBox();
			TextBox* spDefense = new TextBox();
			TextBox* speed = new TextBox();

			attack->dynamic_text = &rosterData->pausePokemonData.attack;
			defense->dynamic_text = &rosterData->pausePokemonData.defense;
			spAttack->dynamic_text = &rosterData->pausePokemonData.spAttack;
			spDefense->dynamic_text = &rosterData->pausePokemonData.spDefense;
			speed->dynamic_text = &rosterData->pausePokemonData.speed;

			attack->renderData = TextBoxRenderData{ 33.0f,		(253.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			defense->renderData = TextBoxRenderData{ 33.0f,		(213.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			spAttack->renderData = TextBoxRenderData{ 33.0f,		(173.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			spDefense->renderData = TextBoxRenderData{ 33.0f,	(133.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			speed->renderData = TextBoxRenderData{ 33.0f,		(93.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };

			pauseRosterMenu.addTextBox(attack);
			pauseRosterMenu.addTextBox(defense);
			pauseRosterMenu.addTextBox(spAttack);
			pauseRosterMenu.addTextBox(spDefense);
			pauseRosterMenu.addTextBox(speed);

			pauseRosterMenu.addRectangle(new RectangleRenderData{ 13.7f, (338.0f / 563.0f) * 100.0f, (11.0f / 563.0f) * 100.0f, &rosterData->pausePokemonData.hpPercent });
		}

		// Move Data
		{
			TextBox* moveText = new TextBox();

			TextBox* move1Name = new TextBox();
			TextBox* move2Name = new TextBox();
			TextBox* move3Name = new TextBox();
			TextBox* move4Name = new TextBox();

			TextBox* currentPP1 = new TextBox();
			TextBox* currentPP2 = new TextBox();
			TextBox* currentPP3 = new TextBox();
			TextBox* currentPP4 = new TextBox();

			TextBox* maxPP1 = new TextBox();
			TextBox* maxPP2 = new TextBox();
			TextBox* maxPP3 = new TextBox();
			TextBox* maxPP4 = new TextBox();

			moveText->text = "MOVES";

			move1Name->dynamic_text = &rosterData->pausePokemonData.move1.moveName;
			move2Name->dynamic_text = &rosterData->pausePokemonData.move2.moveName;
			move3Name->dynamic_text = &rosterData->pausePokemonData.move3.moveName;
			move4Name->dynamic_text = &rosterData->pausePokemonData.move4.moveName;

			currentPP1->dynamic_text = &rosterData->pausePokemonData.move1.currentPP;
			currentPP2->dynamic_text = &rosterData->pausePokemonData.move2.currentPP;
			currentPP3->dynamic_text = &rosterData->pausePokemonData.move3.currentPP;
			currentPP4->dynamic_text = &rosterData->pausePokemonData.move4.currentPP;

			maxPP1->dynamic_text = &rosterData->pausePokemonData.move1.maxPP;
			maxPP2->dynamic_text = &rosterData->pausePokemonData.move2.maxPP;
			maxPP3->dynamic_text = &rosterData->pausePokemonData.move3.maxPP;
			maxPP4->dynamic_text = &rosterData->pausePokemonData.move4.maxPP;

			moveText->renderData = TextBoxRenderData{ 84.0f, (473.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK };

			move1Name->renderData = TextBoxRenderData{ 74.0f, (373.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			move2Name->renderData = TextBoxRenderData{ 74.0f, (283.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			move3Name->renderData = TextBoxRenderData{ 74.0f, (193.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			move4Name->renderData = TextBoxRenderData{ 74.0f, (103.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };

			currentPP1->renderData = TextBoxRenderData{ (875.0f / 1000.0f) * 100.0f, (330.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			currentPP2->renderData = TextBoxRenderData{ (875.0f / 1000.0f) * 100.0f, (240.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			currentPP3->renderData = TextBoxRenderData{ (875.0f / 1000.0f) * 100.0f, (150.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			currentPP4->renderData = TextBoxRenderData{ (875.0f / 1000.0f) * 100.0f, (60.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };

			maxPP1->renderData = TextBoxRenderData{ (890.0f / 1000.0f) * 100.0f, (330.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			maxPP2->renderData = TextBoxRenderData{ (890.0f / 1000.0f) * 100.0f, (240.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			maxPP3->renderData = TextBoxRenderData{ (890.0f / 1000.0f) * 100.0f, (150.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			maxPP4->renderData = TextBoxRenderData{ (890.0f / 1000.0f) * 100.0f, (60.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };


			pauseRosterMenu.addImage(new ImageRenderData{ 77.0f, (353.0f / 563.0f) * 100.0f, 3.0f, 1.5f, " " ,&rosterData->pausePokemonData.move1.moveTypeTextureLocation });
			pauseRosterMenu.addImage(new ImageRenderData{ 77.0f, (263.0f / 563.0f) * 100.0f, 3.0f, 1.5f, " " ,&rosterData->pausePokemonData.move2.moveTypeTextureLocation });
			pauseRosterMenu.addImage(new ImageRenderData{ 77.0f, (173.0f / 563.0f) * 100.0f, 3.0f, 1.5f, " " ,&rosterData->pausePokemonData.move3.moveTypeTextureLocation });
			pauseRosterMenu.addImage(new ImageRenderData{ 77.0f, (83.0f / 563.0f) * 100.0f, 3.0f, 1.5f, " " ,&rosterData->pausePokemonData.move4.moveTypeTextureLocation });

			pauseRosterMenu.addTextBox(moveText);

			pauseRosterMenu.addTextBox(move1Name);
			pauseRosterMenu.addTextBox(move2Name);
			pauseRosterMenu.addTextBox(move3Name);
			pauseRosterMenu.addTextBox(move4Name);

			pauseRosterMenu.addTextBox(currentPP1);
			pauseRosterMenu.addTextBox(currentPP2);
			pauseRosterMenu.addTextBox(currentPP3);
			pauseRosterMenu.addTextBox(currentPP4);

			pauseRosterMenu.addTextBox(maxPP1);
			pauseRosterMenu.addTextBox(maxPP2);
			pauseRosterMenu.addTextBox(maxPP3);
			pauseRosterMenu.addTextBox(maxPP4);
		}

		pokemonName->dynamic_text = &rosterData->pausePokemonData.name;
		pokemonLevel->dynamic_text = &rosterData->pausePokemonData.level;
		pokemonHealth->dynamic_text = &rosterData->pausePokemonData.health;

		pokemonName->renderData = TextBoxRenderData{ 15.0f, 82.0f, 4.0f, Color::BLACK };
		pokemonLevel->renderData = TextBoxRenderData{ 21.1f, 91.3f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		pokemonHealth->renderData = TextBoxRenderData{ 20.0f, 61.0f, 5.0f, Color::BLACK };

		pauseRosterMenu.addTextBox(pokemonName);
		pauseRosterMenu.addTextBox(pokemonLevel);
		pauseRosterMenu.addTextBox(pokemonHealth);


		pauseRosterMenu.addImage(new ImageRenderData{ 15.0f, 75.0f, 5.0f, 2.5f, "", &rosterData->pausePokemonData.type1 });
		pauseRosterMenu.addImage(new ImageRenderData{ 25.0f, 75.0f, 5.0f, 2.5f, "", &rosterData->pausePokemonData.type2 });

		float statusWidth = 3.0f;
		float statusHeight = statusWidth / 2.0f;

		pauseRosterMenu.addImage(new ImageRenderData{ 23.3f, 89.8f, statusWidth, statusHeight, "", &rosterData->pausePokemonData.majorStatusTexture });

		menu->add(MenuScene::PAUSE_ROSTER, pauseRosterMenu);

		Scene battleRoster = pauseRosterMenu;
		battleRoster.setReturnOverlay(MenuOverlay::BATTLE_OPTIONS);
		menu->add(MenuScene::BATTLE_ROSTER, battleRoster);

	}

	// Change Control Overlay
	{
		Overlay changeInput(menu->getRenderer());
		changeInput.setOverlayBackground(new ImageRenderData{ 50.0f, 55.0f, 30.0f, 15.0f, g_overlayTextureLocations[MenuOverlay::DELETE_CONFIRMATION] });

		TextBox* pressNewKey = new TextBox();

		pressNewKey->text = "PRESS NEW INPUT";

		pressNewKey->renderData = TextBoxRenderData{ 50.0f, 50.0f, 5.0f };

		changeInput.addTextBox(pressNewKey);
		menu->add(MenuOverlay::CHANGE_INPUT, changeInput);
	}

	// Pause Settings Menu
	{
		Scene pauseControlsMenu(menu->getRenderer());
		pauseControlsMenu.setBackgroundPath(g_sceneTextureLocations[MenuScene::PAUSE_SETTINGS]);

		float buttonY = (float)56.57193606;			// Correct
		float heightGap = (float)5.328596803f;			// Correct
		float widthGap = 8.2f;					// Correct

		float keyboardX = 18.7f;				// Correct
		float generalX = 60.0f;					// Kinda TODO: Correct for Resolution
		float controllerX = 85.3f;				// Correct

		float buttonWidth = 4.25f;				// Correct
		float buttonHeight = 2.4f;				// Correct

		Button* keyboardUpMain = new Button;
		Button* keyboardUpAlt = new Button;
		Button* keyboardDownMain = new Button;
		Button* keyboardDownAlt = new Button;
		Button* keyboardLeftMain = new Button;
		Button* keyboardLeftAlt = new Button;
		Button* keyboardRightMain = new Button;
		Button* keyboardRightAlt = new Button;
		Button* keyboardSelectMain = new Button;
		Button* keyboardSelectAlt = new Button;
		Button* keyboardBackMain = new Button;
		Button* keyboardBackAlt = new Button;
		Button* keyboardPauseMain = new Button;
		Button* keyboardPauseAlt = new Button;
		Button* keyboardSprintMain = new Button;
		Button* keyboardSprintAlt = new Button;

		Button* controllerUpMain = new Button;
		Button* controllerUpAlt = new Button;
		Button* controllerDownMain = new Button;
		Button* controllerDownAlt = new Button;
		Button* controllerLeftMain = new Button;
		Button* controllerLeftAlt = new Button;
		Button* controllerRightMain = new Button;
		Button* controllerRightAlt = new Button;
		Button* controllerSelectMain = new Button;
		Button* controllerSelectAlt = new Button;
		Button* controllerBackMain = new Button;
		Button* controllerBackAlt = new Button;
		Button* controllerPauseMain = new Button;
		Button* controllerPauseAlt = new Button;
		Button* controllerSprintMain = new Button;
		Button* controllerSprintAlt = new Button;

		Button* generalResolution = new Button;
		Button* generalFullscreen = new Button;
		Button* generalShowFps = new Button;
		Button* generalAutoSave = new Button;
		Button* generalFasterText = new Button;

		// Keyboard Buttons
		{

			// Data
			{
				keyboardUpMain->data = 0;
				keyboardUpAlt->data = 1;
				keyboardDownMain->data = 2;
				keyboardDownAlt->data = 3;
				keyboardLeftMain->data = 4;
				keyboardLeftAlt->data = 5;
				keyboardRightMain->data = 6;
				keyboardRightAlt->data = 7;
				keyboardSelectMain->data = 8;
				keyboardSelectAlt->data = 9;
				keyboardBackMain->data = 10;
				keyboardBackAlt->data = 11;
				keyboardPauseMain->data = 12;
				keyboardPauseAlt->data = 13;
				keyboardSprintMain->data = 14;
				keyboardSprintAlt->data = 15;
			}

			// Text
			{
				keyboardUpMain->dynamic_text = &settingData->keyboardData.UpMain;
				keyboardUpAlt->dynamic_text = &settingData->keyboardData.UpAlt;
				keyboardDownMain->dynamic_text = &settingData->keyboardData.DownMain;
				keyboardDownAlt->dynamic_text = &settingData->keyboardData.DownAlt;
				keyboardLeftMain->dynamic_text = &settingData->keyboardData.LeftMain;
				keyboardLeftAlt->dynamic_text = &settingData->keyboardData.LeftAlt;
				keyboardRightMain->dynamic_text = &settingData->keyboardData.RightMain;
				keyboardRightAlt->dynamic_text = &settingData->keyboardData.RightAlt;
				keyboardSelectMain->dynamic_text = &settingData->keyboardData.SelectMain;
				keyboardSelectAlt->dynamic_text = &settingData->keyboardData.SelectAlt;
				keyboardBackMain->dynamic_text = &settingData->keyboardData.BackMain;
				keyboardBackAlt->dynamic_text = &settingData->keyboardData.BackAlt;
				keyboardPauseMain->dynamic_text = &settingData->keyboardData.PauseMain;
				keyboardPauseAlt->dynamic_text = &settingData->keyboardData.PauseAlt;
				keyboardSprintMain->dynamic_text = &settingData->keyboardData.SprintMain;
				keyboardSprintAlt->dynamic_text = &settingData->keyboardData.SprintAlt;

			}

			// Link
			{
				keyboardUpMain->down = keyboardDownMain;
				keyboardUpMain->right = keyboardUpAlt;

				keyboardDownMain->up = keyboardUpMain;
				keyboardDownMain->down = keyboardLeftMain;
				keyboardDownMain->right = keyboardDownAlt;

				keyboardLeftMain->up = keyboardDownMain;
				keyboardLeftMain->down = keyboardRightMain;
				keyboardLeftMain->right = keyboardLeftAlt;

				keyboardRightMain->up = keyboardLeftMain;
				keyboardRightMain->down = keyboardSelectMain;
				keyboardRightMain->right = keyboardRightAlt;

				keyboardSelectMain->up = keyboardRightMain;
				keyboardSelectMain->down = keyboardBackMain;
				keyboardSelectMain->right = keyboardSelectAlt;

				keyboardBackMain->up = keyboardSelectMain;
				keyboardBackMain->down = keyboardPauseMain;
				keyboardBackMain->right = keyboardBackAlt;

				keyboardPauseMain->up = keyboardBackMain;
				keyboardPauseMain->down = keyboardSprintMain;
				keyboardPauseMain->right = keyboardPauseAlt;

				keyboardSprintMain->up = keyboardPauseMain;
				keyboardSprintMain->right = keyboardSprintAlt;


				keyboardUpAlt->down = keyboardDownAlt;
				keyboardUpAlt->left = keyboardUpMain;
				keyboardUpAlt->right = generalResolution;

				keyboardDownAlt->up = keyboardUpAlt;
				keyboardDownAlt->down = keyboardLeftAlt;
				keyboardDownAlt->left = keyboardDownMain;
				keyboardDownAlt->right = generalFullscreen;

				keyboardLeftAlt->up = keyboardDownAlt;
				keyboardLeftAlt->down = keyboardRightAlt;
				keyboardLeftAlt->left = keyboardLeftMain;
				keyboardLeftAlt->right = generalShowFps;

				keyboardRightAlt->up = keyboardLeftAlt;
				keyboardRightAlt->down = keyboardSelectAlt;
				keyboardRightAlt->left = keyboardRightMain;
				keyboardRightAlt->right = generalAutoSave;

				keyboardSelectAlt->up = keyboardRightAlt;
				keyboardSelectAlt->down = keyboardBackAlt;
				keyboardSelectAlt->left = keyboardSelectMain;
				keyboardSelectAlt->right = generalFasterText;

				keyboardBackAlt->up = keyboardSelectAlt;
				keyboardBackAlt->down = keyboardPauseAlt;
				keyboardBackAlt->left = keyboardBackMain;
				keyboardBackAlt->right = generalFasterText;

				keyboardPauseAlt->up = keyboardBackAlt;
				keyboardPauseAlt->down = keyboardSprintAlt;
				keyboardPauseAlt->left = keyboardPauseMain;
				keyboardPauseAlt->right = generalFasterText;

				keyboardSprintAlt->up = keyboardPauseAlt;
				keyboardSprintAlt->left = keyboardSprintMain;
				keyboardSprintAlt->right = generalFasterText;
			}

			// Render Data
			{
				keyboardUpMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 0), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardUpAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 0), buttonWidth, buttonHeight,		Color::WHITE };
				keyboardDownMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 1), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardDownAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 1), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardLeftMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 2), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardLeftAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 2), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardRightMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 3), buttonWidth, buttonHeight, Color::WHITE };
				keyboardRightAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 3), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardSelectMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 4), buttonWidth, buttonHeight,Color::WHITE };
				keyboardSelectAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 4), buttonWidth, buttonHeight, Color::WHITE };
				keyboardBackMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 5), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardBackAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 5), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardPauseMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 6), buttonWidth, buttonHeight, Color::WHITE };
				keyboardPauseAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 6), buttonWidth, buttonHeight,	Color::WHITE };
				keyboardSprintMain->renderData = ButtonRenderData{ keyboardX + (widthGap * 0), buttonY - (heightGap * 7), buttonWidth, buttonHeight,Color::WHITE };
				keyboardSprintAlt->renderData = ButtonRenderData{ keyboardX + (widthGap * 1), buttonY - (heightGap * 7), buttonWidth, buttonHeight, Color::WHITE };
			}

			// Overlay
			{
				keyboardUpMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardUpAlt->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardDownMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardDownAlt->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardLeftMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardLeftAlt->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardRightMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardRightAlt->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardSelectMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardSelectAlt->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardBackMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardBackAlt->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardPauseMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardPauseAlt->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardSprintMain->overlay = MenuOverlay::CHANGE_INPUT;
				keyboardSprintAlt->overlay = MenuOverlay::CHANGE_INPUT;
			}


		}

		// General Buttons

		{
			// Data
			{
				generalResolution->data = 16;
				generalFullscreen->data = 17;
				generalShowFps->data = 18;
				generalAutoSave->data = 19;
				generalFasterText->data = 20;

				generalResolution->overlay = MenuOverlay::RESOLUTION_SELECTION;
			}

			// Text
			{
				generalResolution->dynamic_text = &settingData->resolution;
				generalFullscreen->dynamic_text = &settingData->fullscreen;
				generalShowFps->dynamic_text = &settingData->showFps;
				generalAutoSave->dynamic_text = &settingData->autoSave;
				generalFasterText->dynamic_text = &settingData->fasterText;
			}

			// Link
			{
				generalResolution->left = keyboardUpAlt;
				generalResolution->down = generalFullscreen;
				generalResolution->right = controllerUpMain;

				generalFullscreen->up = generalResolution;
				generalFullscreen->down = generalShowFps;
				generalFullscreen->left = keyboardDownAlt;
				generalFullscreen->right = controllerDownMain;

				generalShowFps->up = generalFullscreen;
				generalShowFps->down = generalAutoSave;
				generalShowFps->left = keyboardLeftAlt;
				generalShowFps->right = controllerLeftMain;

				generalAutoSave->up = generalShowFps;
				generalAutoSave->left = keyboardRightAlt;
				generalAutoSave->down = generalFasterText;
				generalAutoSave->right = controllerRightMain;

				generalFasterText->up = generalAutoSave;
				generalFasterText->left = keyboardSelectAlt;
				generalFasterText->right = controllerSelectMain;
			}

			// Render Data
			{
				generalResolution->renderData = ButtonRenderData{ generalX - (buttonWidth / 2.0f), buttonY - (heightGap * 0), buttonWidth * 2, buttonHeight, Color::WHITE };
				generalFullscreen->renderData = ButtonRenderData{ generalX, buttonY - (heightGap * 1), buttonWidth, buttonHeight, Color::WHITE };
				generalShowFps->renderData = ButtonRenderData{ generalX, buttonY - (heightGap * 2), buttonWidth, buttonHeight, Color::WHITE };
				generalAutoSave->renderData = ButtonRenderData{ generalX, buttonY - (heightGap * 3), buttonWidth, buttonHeight, Color::WHITE };
				generalFasterText->renderData = ButtonRenderData{ generalX, buttonY - (heightGap * 4), buttonWidth, buttonHeight, Color::WHITE };
			}

			// Pause Resolution Selection
			{
				Overlay resolutionSelection(menu->getRenderer());
				resolutionSelection.setOverlayBackground(new ImageRenderData{ generalX - (buttonWidth / 2.0f), buttonY - (heightGap * 1), buttonWidth + (buttonWidth / 2.0f), buttonHeight * 2, g_overlayTextureLocations[MenuOverlay::DELETE_CONFIRMATION] });

				Button* resolutionSmall = new Button;
				Button* resolutionMedium = new Button;
				Button* resolutionLarge = new Button;

				resolutionSmall->text = "1280x720";
				resolutionMedium->text = "1920x1080";
				resolutionLarge->text = "2560x1440";

				resolutionSmall->data = RendererResolutiion::_1280x720;
				resolutionMedium->data = RendererResolutiion::_1920x1080;
				resolutionLarge->data = RendererResolutiion::_2560x1440;

				resolutionSmall->down = resolutionMedium;
				resolutionMedium->up = resolutionSmall;
				resolutionMedium->down = resolutionLarge;
				resolutionLarge->up = resolutionMedium;

				resolutionSmall->renderData = ButtonRenderData{ generalX - (buttonWidth / 2.0f), buttonY - ((heightGap / 2.0f) * 1), buttonWidth * 2, buttonHeight, Color::WHITE };
				resolutionMedium->renderData = ButtonRenderData{ generalX - (buttonWidth / 2.0f), buttonY - ((heightGap / 2.0f) * 2), buttonWidth * 2, buttonHeight, Color::WHITE };
				resolutionLarge->renderData = ButtonRenderData{ generalX - (buttonWidth / 2.0f), buttonY - ((heightGap / 2.0f) * 3), buttonWidth * 2, buttonHeight, Color::WHITE };

				resolutionSelection.addButton(resolutionSmall);
				resolutionSelection.addButton(resolutionMedium);
				resolutionSelection.addButton(resolutionLarge);

				menu->add(MenuOverlay::RESOLUTION_SELECTION, resolutionSelection);

			}
		}


		// Controller Buttons
		{

			// Data
			{
				controllerUpMain->data = 21;
				controllerUpAlt->data = 22;
				controllerDownMain->data = 23;
				controllerDownAlt->data = 24;
				controllerLeftMain->data = 25;
				controllerLeftAlt->data = 26;
				controllerRightMain->data = 27;
				controllerRightAlt->data = 28;
				controllerSelectMain->data = 29;
				controllerSelectAlt->data = 30;
				controllerBackMain->data = 31;
				controllerBackAlt->data = 32;
				controllerPauseMain->data = 33;
				controllerPauseAlt->data = 34;
				controllerSprintMain->data = 35;
				controllerSprintAlt->data = 36;
			}

			// Text
			{
				controllerUpMain->dynamic_text = &settingData->controllerData.UpMain;
				controllerUpAlt->dynamic_text = &settingData->controllerData.UpAlt;
				controllerDownMain->dynamic_text = &settingData->controllerData.DownMain;
				controllerDownAlt->dynamic_text = &settingData->controllerData.DownAlt;
				controllerLeftMain->dynamic_text = &settingData->controllerData.LeftMain;
				controllerLeftAlt->dynamic_text = &settingData->controllerData.LeftAlt;
				controllerRightMain->dynamic_text = &settingData->controllerData.RightMain;
				controllerRightAlt->dynamic_text = &settingData->controllerData.RightAlt;
				controllerSelectMain->dynamic_text = &settingData->controllerData.SelectMain;
				controllerSelectAlt->dynamic_text = &settingData->controllerData.SelectAlt;
				controllerBackMain->dynamic_text = &settingData->controllerData.BackMain;
				controllerBackAlt->dynamic_text = &settingData->controllerData.BackAlt;
				controllerPauseMain->dynamic_text = &settingData->controllerData.PauseMain;
				controllerPauseAlt->dynamic_text = &settingData->controllerData.PauseAlt;
				controllerSprintMain->dynamic_text = &settingData->controllerData.SprintMain;
				controllerSprintAlt->dynamic_text = &settingData->controllerData.SprintAlt;
			}

			// Link
			{
				controllerUpMain->down = controllerDownMain;
				controllerUpMain->right = controllerUpAlt;
				controllerUpMain->left = generalResolution;

				controllerDownMain->up = controllerUpMain;
				controllerDownMain->down = controllerLeftMain;
				controllerDownMain->right = controllerDownAlt;
				controllerDownMain->left = generalFullscreen;

				controllerLeftMain->up = controllerDownMain;
				controllerLeftMain->down = controllerRightMain;
				controllerLeftMain->right = controllerLeftAlt;
				controllerLeftMain->left = generalShowFps;

				controllerRightMain->up = controllerLeftMain;
				controllerRightMain->down = controllerSelectMain;
				controllerRightMain->right = controllerRightAlt;
				controllerRightMain->left = generalAutoSave;

				controllerSelectMain->up = controllerRightMain;
				controllerSelectMain->down = controllerBackMain;
				controllerSelectMain->right = controllerSelectAlt;
				controllerSelectMain->left = generalFasterText;

				controllerBackMain->up = controllerSelectMain;
				controllerBackMain->down = controllerPauseMain;
				controllerBackMain->right = controllerBackAlt;
				controllerBackMain->left = generalFasterText;

				controllerPauseMain->up = controllerBackMain;
				controllerPauseMain->down = controllerSprintMain;
				controllerPauseMain->right = controllerPauseAlt;
				controllerPauseMain->left = generalFasterText;

				controllerSprintMain->up = controllerPauseMain;
				controllerSprintMain->right = controllerSprintAlt;
				controllerSprintMain->left = generalFasterText;

				controllerUpAlt->down = controllerDownAlt;
				controllerUpAlt->left = controllerUpMain;

				controllerDownAlt->up = controllerUpAlt;
				controllerDownAlt->down = controllerLeftAlt;
				controllerDownAlt->left = controllerDownMain;

				controllerLeftAlt->up = controllerDownAlt;
				controllerLeftAlt->down = controllerRightAlt;
				controllerLeftAlt->left = controllerLeftMain;

				controllerRightAlt->up = controllerLeftAlt;
				controllerRightAlt->down = controllerSelectAlt;
				controllerRightAlt->left = controllerRightMain;

				controllerSelectAlt->up = controllerRightAlt;
				controllerSelectAlt->down = controllerBackAlt;
				controllerSelectAlt->left = controllerSelectMain;

				controllerBackAlt->up = controllerSelectAlt;
				controllerBackAlt->down = controllerPauseAlt;
				controllerBackAlt->left = controllerBackMain;

				controllerPauseAlt->up = controllerBackAlt;
				controllerPauseAlt->down = controllerSprintAlt;
				controllerPauseAlt->left = controllerPauseMain;

				controllerSprintAlt->up = controllerPauseAlt;
				controllerSprintAlt->left = controllerSprintMain;
			}

			// Render Data
			{
				controllerUpMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 0), buttonWidth, buttonHeight,	Color::WHITE };
				controllerUpAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 0), buttonWidth, buttonHeight,		Color::WHITE };
				controllerDownMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 1), buttonWidth, buttonHeight,	Color::WHITE };
				controllerDownAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 1), buttonWidth, buttonHeight,	Color::WHITE };
				controllerLeftMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 2), buttonWidth, buttonHeight,	Color::WHITE };
				controllerLeftAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 2), buttonWidth, buttonHeight,	Color::WHITE };
				controllerRightMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 3), buttonWidth, buttonHeight, Color::WHITE };
				controllerRightAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 3), buttonWidth, buttonHeight,	Color::WHITE };
				controllerSelectMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 4), buttonWidth, buttonHeight,Color::WHITE };
				controllerSelectAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 4), buttonWidth, buttonHeight, Color::WHITE };
				controllerBackMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 5), buttonWidth, buttonHeight,	Color::WHITE };
				controllerBackAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 5), buttonWidth, buttonHeight,	Color::WHITE };
				controllerPauseMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 6), buttonWidth, buttonHeight, Color::WHITE };
				controllerPauseAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 6), buttonWidth, buttonHeight,	Color::WHITE };
				controllerSprintMain->renderData = ButtonRenderData{ controllerX + (widthGap * 0), buttonY - (heightGap * 7), buttonWidth, buttonHeight,Color::WHITE };
				controllerSprintAlt->renderData = ButtonRenderData{ controllerX + (widthGap * 1), buttonY - (heightGap * 7), buttonWidth, buttonHeight, Color::WHITE };
			}

			{
				controllerUpMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerUpAlt->overlay = MenuOverlay::CHANGE_INPUT;
				controllerDownMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerDownAlt->overlay = MenuOverlay::CHANGE_INPUT;
				controllerLeftMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerLeftAlt->overlay = MenuOverlay::CHANGE_INPUT;
				controllerRightMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerRightAlt->overlay = MenuOverlay::CHANGE_INPUT;
				controllerSelectMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerSelectAlt->overlay = MenuOverlay::CHANGE_INPUT;
				controllerBackMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerBackAlt->overlay = MenuOverlay::CHANGE_INPUT;
				controllerPauseMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerPauseAlt->overlay = MenuOverlay::CHANGE_INPUT;
				controllerSprintMain->overlay = MenuOverlay::CHANGE_INPUT;
				controllerSprintAlt->overlay = MenuOverlay::CHANGE_INPUT;

			}
		}


		pauseControlsMenu.addButton(generalResolution);
		pauseControlsMenu.addButton(generalFullscreen);
		pauseControlsMenu.addButton(generalShowFps);
		pauseControlsMenu.addButton(generalAutoSave);
		pauseControlsMenu.addButton(generalFasterText);
		pauseControlsMenu.addButton(keyboardUpMain);
		pauseControlsMenu.addButton(keyboardUpAlt);
		pauseControlsMenu.addButton(keyboardUpMain);
		pauseControlsMenu.addButton(keyboardUpAlt);
		pauseControlsMenu.addButton(keyboardDownMain);
		pauseControlsMenu.addButton(keyboardDownAlt);
		pauseControlsMenu.addButton(keyboardLeftMain);
		pauseControlsMenu.addButton(keyboardLeftAlt);
		pauseControlsMenu.addButton(keyboardRightMain);
		pauseControlsMenu.addButton(keyboardRightAlt);
		pauseControlsMenu.addButton(keyboardSelectMain);
		pauseControlsMenu.addButton(keyboardSelectAlt);
		pauseControlsMenu.addButton(keyboardBackMain);
		pauseControlsMenu.addButton(keyboardBackAlt);
		pauseControlsMenu.addButton(keyboardPauseMain);
		pauseControlsMenu.addButton(keyboardPauseAlt);
		pauseControlsMenu.addButton(keyboardSprintMain);
		pauseControlsMenu.addButton(keyboardSprintAlt);
		pauseControlsMenu.addButton(controllerUpMain);
		pauseControlsMenu.addButton(controllerUpAlt);
		pauseControlsMenu.addButton(controllerUpMain);
		pauseControlsMenu.addButton(controllerUpAlt);
		pauseControlsMenu.addButton(controllerDownMain);
		pauseControlsMenu.addButton(controllerDownAlt);
		pauseControlsMenu.addButton(controllerLeftMain);
		pauseControlsMenu.addButton(controllerLeftAlt);
		pauseControlsMenu.addButton(controllerRightMain);
		pauseControlsMenu.addButton(controllerRightAlt);
		pauseControlsMenu.addButton(controllerSelectMain);
		pauseControlsMenu.addButton(controllerSelectAlt);
		pauseControlsMenu.addButton(controllerBackMain);
		pauseControlsMenu.addButton(controllerBackAlt);
		pauseControlsMenu.addButton(controllerPauseMain);
		pauseControlsMenu.addButton(controllerPauseAlt);
		pauseControlsMenu.addButton(controllerSprintMain);
		pauseControlsMenu.addButton(controllerSprintAlt);

		menu->add(MenuScene::PAUSE_SETTINGS, pauseControlsMenu);
	}




	// Bag
	{
		Scene pauseBagMenu(menu->getRenderer());
		pauseBagMenu.setBackgroundPath(g_sceneTextureLocations[MenuScene::BATTLE_ITEMS]);

		Button* upArrow = new Button;
		Button* downArrow = new Button;

		Button* bagIndex0 = new Button;
		Button* bagIndex1 = new Button;
		Button* bagIndex2 = new Button;
		Button* bagIndex3 = new Button;
		Button* bagIndex4 = new Button;

		TextBox* item1Name = new TextBox;
		TextBox* item2Name = new TextBox;
		TextBox* item3Name = new TextBox;
		TextBox* item4Name = new TextBox;
		TextBox* item5Name = new TextBox;

		TextBox* item1Amount = new TextBox;
		TextBox* item2Amount = new TextBox;
		TextBox* item3Amount = new TextBox;
		TextBox* item4Amount = new TextBox;
		TextBox* item5Amount = new TextBox;

		upArrow->data = arrowDirections::UP;
		downArrow->data = arrowDirections::DOWN;

		bagIndex0->data = 0;
		bagIndex1->data = 1;
		bagIndex2->data = 2;
		bagIndex3->data = 3;
		bagIndex4->data = 4;


		upArrow->up = downArrow;
		upArrow->down = bagIndex0;

		bagIndex0->up = upArrow;
		bagIndex0->down = bagIndex1;

		bagIndex1->up = bagIndex0;
		bagIndex1->down = bagIndex2;

		bagIndex2->up = bagIndex1;
		bagIndex2->down = bagIndex3;

		bagIndex3->up = bagIndex2;
		bagIndex3->down = bagIndex4;

		bagIndex4->up = bagIndex3;
		bagIndex4->down = downArrow;

		downArrow->up = bagIndex4;
		downArrow->down = upArrow;


		upArrow->text = "UP";
		item1Name->dynamic_text = &items->itemName.string1;
		item2Name->dynamic_text = &items->itemName.string2;
		item3Name->dynamic_text = &items->itemName.string3;
		item4Name->dynamic_text = &items->itemName.string4;
		item5Name->dynamic_text = &items->itemName.string5;
		downArrow->text = "DOWN";

		item1Amount->dynamic_text = &items->itemAmount.string1;
		item2Amount->dynamic_text = &items->itemAmount.string2;
		item3Amount->dynamic_text = &items->itemAmount.string3;
		item4Amount->dynamic_text = &items->itemAmount.string4;
		item5Amount->dynamic_text = &items->itemAmount.string5;


		{
			float topX = 50.0f;
			float topY = 90.0f;

			float buttonGap = 13.0f;

			float width = 30.0f;
			float height = 10.0f;

			Color color = Color::BUTTER_SCOTCH;

			upArrow->renderData = ButtonRenderData{ topX, topY - (buttonGap * 0), width, height, color };
			bagIndex0->renderData = ButtonRenderData{ topX, topY - (buttonGap * 1), width, height, color };
			bagIndex1->renderData = ButtonRenderData{ topX, topY - (buttonGap * 2), width, height, color };
			bagIndex2->renderData = ButtonRenderData{ topX, topY - (buttonGap * 3), width, height, color };
			bagIndex3->renderData = ButtonRenderData{ topX, topY - (buttonGap * 4), width, height, color };
			bagIndex4->renderData = ButtonRenderData{ topX, topY - (buttonGap * 5), width, height, color };
			downArrow->renderData = ButtonRenderData{ topX, topY - (buttonGap * 6), width, height, color };

			float pixels = 20.0f;
			float innerOffset = 2.0f;

			//Images are what causes things to slow
			pauseBagMenu.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 1), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });
			pauseBagMenu.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 2), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });
			pauseBagMenu.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 3), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });
			pauseBagMenu.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 4), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });
			pauseBagMenu.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 5), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME], nullptr, nullptr });

			pauseBagMenu.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 1), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &items->itemTexture.string1, nullptr });
			pauseBagMenu.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 2), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &items->itemTexture.string2, nullptr });
			pauseBagMenu.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 3), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &items->itemTexture.string3, nullptr });
			pauseBagMenu.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 4), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &items->itemTexture.string4, nullptr });
			pauseBagMenu.addImage(new ImageRenderData{ topX - 12.0f, topY - (buttonGap * 5), ((pixels - innerOffset) / 1000.0f) * 100.0f, ((pixels - innerOffset) / 563.0f) * 100.0f, "", &items->itemTexture.string5, nullptr });

			item1Name->renderData = TextBoxRenderData{ topX - 9.0f, topY - (buttonGap * 1) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			item2Name->renderData = TextBoxRenderData{ topX - 9.0f, topY - (buttonGap * 2) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			item3Name->renderData = TextBoxRenderData{ topX - 9.0f, topY - (buttonGap * 3) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			item4Name->renderData = TextBoxRenderData{ topX - 9.0f, topY - (buttonGap * 4) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			item5Name->renderData = TextBoxRenderData{ topX - 9.0f, topY - (buttonGap * 5) - 2.0f , 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };

			item1Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 1) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			item2Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 2) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			item3Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 3) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			item4Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 4) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			item5Amount->renderData = TextBoxRenderData{ topX + 14.0f, topY - (buttonGap * 5) - 2.0f , 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		}


		pauseBagMenu.addTextBox(item1Name);
		pauseBagMenu.addTextBox(item2Name);
		pauseBagMenu.addTextBox(item3Name);
		pauseBagMenu.addTextBox(item4Name);
		pauseBagMenu.addTextBox(item5Name);

		pauseBagMenu.addTextBox(item1Amount);
		pauseBagMenu.addTextBox(item2Amount);
		pauseBagMenu.addTextBox(item3Amount);
		pauseBagMenu.addTextBox(item4Amount);
		pauseBagMenu.addTextBox(item5Amount);

		pauseBagMenu.addButton(bagIndex0);
		pauseBagMenu.addButton(bagIndex1);
		pauseBagMenu.addButton(bagIndex2);
		pauseBagMenu.addButton(bagIndex3);
		pauseBagMenu.addButton(bagIndex4);
		pauseBagMenu.addButton(upArrow);
		pauseBagMenu.addButton(downArrow);

		menu->add(MenuScene::PAUSE_BAG, pauseBagMenu);
	}

	// Save confirmation
	{
		Overlay saveConfirmation(menu->getRenderer());
		saveConfirmation.setOverlayBackground(new ImageRenderData{ 50.0f, 50.0f, 20.0f, 20.0f, g_overlayTextureLocations[MenuOverlay::DELETE_CONFIRMATION] });

		TextBox* saveMessage = new TextBox;
		Button* ok = new Button;

		saveMessage->text = "SAVE COMPLETE";
		ok->text = "OK";
		ok->data = 0;

		saveMessage->renderData = TextBoxRenderData{ 50.0f, 50.0f, 5.0f };
		ok->renderData = ButtonRenderData{ 50.0f, 40.0f, 10.0f, 7.5f, Color::WHITE };

		saveConfirmation.addButton(ok);
		saveConfirmation.addTextBox(saveMessage);

		menu->add(MenuOverlay::SAVE_COMPLETE, saveConfirmation);
	}
}

void MenuSetup::setupPokedexData(Menu* menu, PokedexDisplayData* pokedexDisplayData)
{
	// Pokedex Menu
	{
		Scene pokedexMenu(menu->getRenderer());
		pokedexMenu.setBackgroundPath(g_sceneTextureLocations[MenuScene::POKEDEX]);

		// Static Text
		{
			TextBox* pokemonName = new TextBox();
			TextBox* pokemonNumber = new TextBox();
			TextBox* pokemonHeight = new TextBox();
			TextBox* pokemonWight = new TextBox();
			TextBox* pokemonDescription = new TextBox();
			TextBox* pokemonSeen = new TextBox();
			TextBox* pokemonCaught = new TextBox();

			pokemonName->dynamic_text = &pokedexDisplayData->pokemonSelectedData.pokemonName;
			pokemonNumber->dynamic_text = &pokedexDisplayData->pokemonSelectedData.pokemonNumber;
			pokemonHeight->dynamic_text = &pokedexDisplayData->pokemonSelectedData.pokemonHeight;
			pokemonWight->dynamic_text = &pokedexDisplayData->pokemonSelectedData.pokemonWight;
			pokemonDescription->dynamic_text = &pokedexDisplayData->pokemonSelectedData.pokemonDescription;
			pokemonSeen->dynamic_text = &pokedexDisplayData->pokemonSeen;
			pokemonCaught->dynamic_text = &pokedexDisplayData->pokemonCaught;

			pokemonName->renderData = TextBoxRenderData{ (260.0f / 1000.0f) * 100.0f, (520.0f / 563.0f) * 100.0f, 4.0f };
			pokemonNumber->renderData = TextBoxRenderData{ (25.0f / 1000.0f) * 100.0f, (538.0f / 563.0f) * 100.0f, 2.5f };
			pokemonHeight->renderData = TextBoxRenderData{ (248.0f / 1000.0f) * 100.0f, (263.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			pokemonWight->renderData = TextBoxRenderData{ (282.0f / 1000.0f) * 100.0f, (263.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
			pokemonDescription->renderData = TextBoxRenderData{ (88.0f / 1000.0f) * 100.0f, (158.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN, 38.0f, 0.547f };
			pokemonSeen->renderData = TextBoxRenderData{ (740.0f / 1000.0f) * 100.0f, (490.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
			pokemonCaught->renderData = TextBoxRenderData{ (764.0f / 1000.0f) * 100.0f, (490.0f / 563.0f) * 100.0f, 3.0f, Color::BLACK, Alignment::LEFT_ALIGN };

			pokedexMenu.addTextBox(pokemonName);
			pokedexMenu.addTextBox(pokemonNumber);
			pokedexMenu.addTextBox(pokemonHeight);
			pokedexMenu.addTextBox(pokemonWight);
			pokedexMenu.addTextBox(pokemonDescription);
			pokedexMenu.addTextBox(pokemonSeen);
			pokedexMenu.addTextBox(pokemonCaught);
		}

		// Display Images
		{

			pokedexDisplayData->pokemonSelectedData.pokemonImage.deleteWithScene = false;
			pokedexDisplayData->pokemonSelectedData.pokemonType1.deleteWithScene = false;
			pokedexDisplayData->pokemonSelectedData.pokemonType2.deleteWithScene = false;
			pokedexDisplayData->sortArrow.deleteWithScene = false;
			pokedexDisplayData->selectionHighlight.deleteWithScene = false;

			pokedexMenu.addDynamicImage(&pokedexDisplayData->pokemonSelectedData.pokemonImage);
			pokedexMenu.addDynamicImage(&pokedexDisplayData->pokemonSelectedData.pokemonType1);
			pokedexMenu.addDynamicImage(&pokedexDisplayData->pokemonSelectedData.pokemonType2);
			pokedexMenu.addDynamicImage(&pokedexDisplayData->sortArrow);
			pokedexMenu.addDynamicImage(&pokedexDisplayData->selectionHighlight);
		}

		//TODO: Make sure that the menu has button3 first

		// Display Scroll Buttons
		{
			// Buttons
			{
				Button* button0 = new Button();
				Button* button1 = new Button();
				Button* button2 = new Button();
				Button* button3 = new Button();	// Center Start
				Button* button4 = new Button();
				Button* button5 = new Button();
				Button* button6 = new Button();

				Button* pokemonNameSort = new Button();
				Button* pokemonNumberSort = new Button();

				pokemonNameSort->data = 0;
				pokemonNumberSort->data = 1;

				button0->up = button6;
				button0->down = button1;
				button0->right = pokemonNameSort;

				button1->up = button0;
				button1->down = button2;
				button1->right = pokemonNameSort;

				button2->up = button1;
				button2->down = button3;
				button2->right = pokemonNameSort;

				button3->up = button2;
				button3->down = button4;
				button3->right = pokemonNameSort;

				button4->up = button3;
				button4->down = button5;
				button4->right = pokemonNameSort;

				button5->up = button4;
				button5->down = button6;
				button5->right = pokemonNameSort;

				button6->up = button5;
				button6->down = button0;
				button6->right = pokemonNameSort;

				pokemonNameSort->down = pokemonNumberSort;
				pokemonNumberSort->up = pokemonNameSort;

				pokemonNameSort->goBackOnLeft = true;
				pokemonNumberSort->goBackOnLeft = true;

				button0->dynamicRenderData = &pokedexDisplayData->button7.buttonRenderData;
				button1->dynamicRenderData = &pokedexDisplayData->button6.buttonRenderData;
				button2->dynamicRenderData = &pokedexDisplayData->button5.buttonRenderData;
				button3->dynamicRenderData = &pokedexDisplayData->button4.buttonRenderData;
				button4->dynamicRenderData = &pokedexDisplayData->button3.buttonRenderData;
				button5->dynamicRenderData = &pokedexDisplayData->button2.buttonRenderData;
				button6->dynamicRenderData = &pokedexDisplayData->button1.buttonRenderData;

				pokemonNameSort->renderData = ButtonRenderData{ 90.0f, 15.0f, 5.0f, 5.0f ,Color::RED, renderOptions::autoSizeText, &pokedexDisplayData->sortButtonsVisible };
				pokemonNumberSort->renderData = ButtonRenderData{ 90.0f, 8.0f, 5.0f, 5.0f, Color::RED, renderOptions::autoSizeText, &pokedexDisplayData->sortButtonsVisible };

				pokedexMenu.addButton(button3); //0
				pokedexMenu.addButton(button0); //1
				pokedexMenu.addButton(button1); //2
				pokedexMenu.addButton(button2); //3
				pokedexMenu.addButton(button4); //4
				pokedexMenu.addButton(button5); //5
				pokedexMenu.addButton(button6); //6

				pokedexMenu.addButton(pokemonNameSort);
				pokedexMenu.addButton(pokemonNumberSort);
			}

			// Pokemon Names
			{
				TextBox* button1PokemonName = new TextBox();
				TextBox* button2PokemonName = new TextBox();
				TextBox* button3PokemonName = new TextBox();
				TextBox* button4PokemonName = new TextBox();
				TextBox* button5PokemonName = new TextBox();
				TextBox* button6PokemonName = new TextBox();
				TextBox* button7PokemonName = new TextBox();

				button1PokemonName->dynamic_text = &pokedexDisplayData->button1.pokemonName.value;
				button2PokemonName->dynamic_text = &pokedexDisplayData->button2.pokemonName.value;
				button3PokemonName->dynamic_text = &pokedexDisplayData->button3.pokemonName.value;
				button4PokemonName->dynamic_text = &pokedexDisplayData->button4.pokemonName.value;
				button5PokemonName->dynamic_text = &pokedexDisplayData->button5.pokemonName.value;
				button6PokemonName->dynamic_text = &pokedexDisplayData->button6.pokemonName.value;
				button7PokemonName->dynamic_text = &pokedexDisplayData->button7.pokemonName.value;

				button1PokemonName->dynamicRenderData = &pokedexDisplayData->button1.pokemonName.renderData;
				button2PokemonName->dynamicRenderData = &pokedexDisplayData->button2.pokemonName.renderData;
				button3PokemonName->dynamicRenderData = &pokedexDisplayData->button3.pokemonName.renderData;
				button4PokemonName->dynamicRenderData = &pokedexDisplayData->button4.pokemonName.renderData;
				button5PokemonName->dynamicRenderData = &pokedexDisplayData->button5.pokemonName.renderData;
				button6PokemonName->dynamicRenderData = &pokedexDisplayData->button6.pokemonName.renderData;
				button7PokemonName->dynamicRenderData = &pokedexDisplayData->button7.pokemonName.renderData;

				pokedexMenu.addTextBox(button1PokemonName);
				pokedexMenu.addTextBox(button2PokemonName);
				pokedexMenu.addTextBox(button3PokemonName);
				pokedexMenu.addTextBox(button4PokemonName);
				pokedexMenu.addTextBox(button5PokemonName);
				pokedexMenu.addTextBox(button6PokemonName);
				pokedexMenu.addTextBox(button7PokemonName);
			}

			// Pokemon Numbers
			{
				TextBox* button1PokemonNumber = new TextBox();
				TextBox* button2PokemonNumber = new TextBox();
				TextBox* button3PokemonNumber = new TextBox();
				TextBox* button4PokemonNumber = new TextBox();
				TextBox* button5PokemonNumber = new TextBox();
				TextBox* button6PokemonNumber = new TextBox();
				TextBox* button7PokemonNumber = new TextBox();

				button1PokemonNumber->dynamic_text = &pokedexDisplayData->button1.pokemonNumber.value;
				button2PokemonNumber->dynamic_text = &pokedexDisplayData->button2.pokemonNumber.value;
				button3PokemonNumber->dynamic_text = &pokedexDisplayData->button3.pokemonNumber.value;
				button4PokemonNumber->dynamic_text = &pokedexDisplayData->button4.pokemonNumber.value;
				button5PokemonNumber->dynamic_text = &pokedexDisplayData->button5.pokemonNumber.value;
				button6PokemonNumber->dynamic_text = &pokedexDisplayData->button6.pokemonNumber.value;
				button7PokemonNumber->dynamic_text = &pokedexDisplayData->button7.pokemonNumber.value;

				button1PokemonNumber->dynamicRenderData = &pokedexDisplayData->button1.pokemonNumber.renderData;
				button2PokemonNumber->dynamicRenderData = &pokedexDisplayData->button2.pokemonNumber.renderData;
				button3PokemonNumber->dynamicRenderData = &pokedexDisplayData->button3.pokemonNumber.renderData;
				button4PokemonNumber->dynamicRenderData = &pokedexDisplayData->button4.pokemonNumber.renderData;
				button5PokemonNumber->dynamicRenderData = &pokedexDisplayData->button5.pokemonNumber.renderData;
				button6PokemonNumber->dynamicRenderData = &pokedexDisplayData->button6.pokemonNumber.renderData;
				button7PokemonNumber->dynamicRenderData = &pokedexDisplayData->button7.pokemonNumber.renderData;

				pokedexMenu.addTextBox(button1PokemonNumber);
				pokedexMenu.addTextBox(button2PokemonNumber);
				pokedexMenu.addTextBox(button3PokemonNumber);
				pokedexMenu.addTextBox(button4PokemonNumber);
				pokedexMenu.addTextBox(button5PokemonNumber);
				pokedexMenu.addTextBox(button6PokemonNumber);
				pokedexMenu.addTextBox(button7PokemonNumber);
			}

			// Pokemon Catch Images
			{

				pokedexDisplayData->button1.pokemonCaughtImage.deleteWithScene = false;
				pokedexDisplayData->button2.pokemonCaughtImage.deleteWithScene = false;
				pokedexDisplayData->button3.pokemonCaughtImage.deleteWithScene = false;
				pokedexDisplayData->button4.pokemonCaughtImage.deleteWithScene = false;
				pokedexDisplayData->button5.pokemonCaughtImage.deleteWithScene = false;
				pokedexDisplayData->button6.pokemonCaughtImage.deleteWithScene = false;
				pokedexDisplayData->button7.pokemonCaughtImage.deleteWithScene = false;

				pokedexMenu.addDynamicImage(&pokedexDisplayData->button1.pokemonCaughtImage);
				pokedexMenu.addDynamicImage(&pokedexDisplayData->button2.pokemonCaughtImage);
				pokedexMenu.addDynamicImage(&pokedexDisplayData->button3.pokemonCaughtImage);
				pokedexMenu.addDynamicImage(&pokedexDisplayData->button4.pokemonCaughtImage);
				pokedexMenu.addDynamicImage(&pokedexDisplayData->button5.pokemonCaughtImage);
				pokedexMenu.addDynamicImage(&pokedexDisplayData->button6.pokemonCaughtImage);
				pokedexMenu.addDynamicImage(&pokedexDisplayData->button7.pokemonCaughtImage);
			}
		}

		menu->add(MenuScene::POKEDEX, pokedexMenu);
	}

	// New Pokemon Scene

	{
		Scene newPokemon(menu->getRenderer());
		newPokemon.setBackgroundPath(g_sceneTextureLocations[MenuScene::NEW_POKEMON]);

		TextBox* pokemonName = new TextBox();
		TextBox* pokemonNumber = new TextBox();
		TextBox* pokemonHeight = new TextBox();
		TextBox* pokemonWeight = new TextBox();
		TextBox* pokemonDescription = new TextBox();


		pokemonName->dynamic_text = &pokedexDisplayData->pokemonSelectedData.pokemonName;
		pokemonNumber->dynamic_text = &pokedexDisplayData->pokemonSelectedData.pokemonNumber;
		pokemonHeight->dynamic_text = &pokedexDisplayData->pokemonSelectedData.pokemonHeight;
		pokemonWeight->dynamic_text = &pokedexDisplayData->pokemonSelectedData.pokemonWight;
		pokemonDescription->dynamic_text = &pokedexDisplayData->pokemonSelectedData.pokemonDescription;

		float yGap = 40.0f;

		pokemonName->renderData = TextBoxRenderData{ 21.0f, ((430.0f - (yGap * 0)) / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		pokemonNumber->renderData = TextBoxRenderData{ 21.0f, ((430.0f - (yGap * 1)) / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		pokemonHeight->renderData = TextBoxRenderData{ 21.0f, ((430.0f - (yGap * 2)) / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		pokemonWeight->renderData = TextBoxRenderData{ 21.0f, ((430.0f - (yGap * 3)) / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		pokemonDescription->renderData = TextBoxRenderData{ 21.0f, (253.0f / 563.0f) * 100.0f, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN, 60.4f, -0.6f };

		newPokemon.addTextBox(pokemonName);
		newPokemon.addTextBox(pokemonNumber);
		newPokemon.addTextBox(pokemonHeight);
		newPokemon.addTextBox(pokemonWeight);
		newPokemon.addTextBox(pokemonDescription);

		pokedexDisplayData->newPokemonImage.deleteWithScene = false;
		newPokemon.addDynamicImage(&pokedexDisplayData->newPokemonImage);

		menu->add(MenuScene::NEW_POKEMON, newPokemon);
	}
}

void MenuSetup::setupPCData(Menu* menu, PCData* pcData)
{
	float topLeftBoxX = (500.0f / 1000.0f) * 100.0f;
	float topLeftBoxY = (450.0f / 563.0f) * 100.0f;

	float boxSizeMulitplier = 1.25f;
	float boxWidth = 9.0f / boxSizeMulitplier;
	float boxHeight = 16.0f / boxSizeMulitplier;

	float boxXGap = boxWidth + ((10.0f / 1000.0f) * 100.0f);
	float boxYGap = boxHeight + ((10.0f / 563.0f) * 100.0f);

	float rosterLeftBoxX = (875.0f / 1000.0f) * 100.0f;
	float rosterLeftBoxY = ((450.0f / 563.0f) * 100.0f) + (boxHeight / 2.0f);
	float rosterBoxOffset = boxHeight / 2.0f;

	//PC Scene
	{
		Scene usePC(menu->getRenderer());

		usePC.setBackgroundPath(g_sceneTextureLocations[MenuScene::USE_PC]);

		Button* leftArrow = new Button;
		Button* rightArrow = new Button;

		Button* boxTitle = new Button;
		Button* box1 = new Button;
		Button* box2 = new Button;
		Button* box3 = new Button;
		Button* box4 = new Button;
		Button* box5 = new Button;
		Button* box6 = new Button;
		Button* box7 = new Button;
		Button* box8 = new Button;
		Button* box9 = new Button;
		Button* box10 = new Button;
		Button* box11 = new Button;
		Button* box12 = new Button;
		Button* box13 = new Button;
		Button* box14 = new Button;
		Button* box15 = new Button;
		Button* box16 = new Button;
		Button* box17 = new Button;
		Button* box18 = new Button;
		Button* box19 = new Button;
		Button* box20 = new Button;
		Button* box21 = new Button;
		Button* box22 = new Button;
		Button* box23 = new Button;
		Button* box24 = new Button;
		Button* box25 = new Button;
		Button* box26 = new Button;
		Button* box27 = new Button;
		Button* box28 = new Button;
		Button* box29 = new Button;
		Button* box30 = new Button;
		Button* roster1 = new Button;
		Button* roster2 = new Button;
		Button* roster3 = new Button;
		Button* roster4 = new Button;
		Button* roster5 = new Button;
		Button* roster6 = new Button;


		leftArrow->data = arrowDirections::LEFT;
		rightArrow->data = arrowDirections::RIGHT;
		boxTitle->data = NONE;

		box1->data = 0;
		box2->data = 1;
		box3->data = 2;
		box4->data = 3;
		box5->data = 4;
		box6->data = 5;
		box7->data = 6;
		box8->data = 7;
		box9->data = 8;
		box10->data = 9;
		box11->data = 10;
		box12->data = 11;
		box13->data = 12;
		box14->data = 13;
		box15->data = 14;
		box16->data = 15;
		box17->data = 16;
		box18->data = 17;
		box19->data = 18;
		box20->data = 19;
		box21->data = 20;
		box22->data = 21;
		box23->data = 22;
		box24->data = 23;
		box25->data = 24;
		box26->data = 25;
		box27->data = 26;
		box28->data = 27;
		box29->data = 28;
		box30->data = 29;
		roster1->data = 30;
		roster2->data = 31;
		roster3->data = 32;
		roster4->data = 33;
		roster5->data = 34;
		roster6->data = 35;

		leftArrow->text = "Left Arrow";
		rightArrow->text = "Right Arrow";
		boxTitle->text = "Box Title";
		box1->text = "Box 1";
		box2->text = "Box 2";
		box3->text = "Box 3";
		box4->text = "Box 4";
		box5->text = "Box 5";
		box6->text = "Box 6";
		box7->text = "Box 7";
		box8->text = "Box 8";
		box9->text = "Box 9";
		box10->text = "Box 10";
		box11->text = "Box 11";
		box12->text = "Box 12";
		box13->text = "Box 13";
		box14->text = "Box 14";
		box15->text = "Box 15";
		box16->text = "Box 16";
		box17->text = "Box 17";
		box18->text = "Box 18";
		box19->text = "Box 19";
		box20->text = "Box 20";
		box21->text = "Box 21";
		box22->text = "Box 22";
		box23->text = "Box 23";
		box24->text = "Box 24";
		box25->text = "Box 25";
		box26->text = "Box 26";
		box27->text = "Box 27";
		box28->text = "Box 28";
		box29->text = "Box 29";
		box30->text = "Box 30";
		roster1->text = "Roster 1";
		roster2->text = "Roster 2";
		roster3->text = "Roster 3";
		roster4->text = "Roster 4";
		roster5->text = "Roster 5";
		roster6->text = "Roster 6";

		leftArrow->down = box1;
		leftArrow->right = boxTitle;

		boxTitle->left = leftArrow;
		boxTitle->right = rightArrow;
		boxTitle->down = box3;

		rightArrow->left = boxTitle;
		rightArrow->down = box5;

		box1->up = boxTitle;
		box1->down = box6;
		box1->right = box2;

		box2->up = boxTitle;
		box2->down = box7;
		box2->left = box1;
		box2->right = box3;

		box3->up = boxTitle;
		box3->down = box8;
		box3->left = box2;
		box3->right = box4;

		box4->up = boxTitle;
		box4->down = box9;
		box4->left = box3;
		box4->right = box5;

		box5->up = boxTitle;
		box5->down = box10;
		box5->left = box4;
		box5->right = roster1;

		box6->up = box1;
		box6->down = box11;
		box6->right = box7;

		box7->up = box2;
		box7->down = box12;
		box7->left = box6;
		box7->right = box8;

		box8->up = box3;
		box8->down = box13;
		box8->left = box7;
		box8->right = box9;

		box9->up = box4;
		box9->down = box14;
		box9->left = box8;
		box9->right = box10;

		box10->up = box5;
		box10->down = box15;
		box10->left = box9;
		box10->right = roster1;

		box11->up = box6;
		box11->down = box16;
		box11->right = box12;

		box12->up = box7;
		box12->down = box17;
		box12->left = box11;
		box12->right = box13;

		box13->up = box8;
		box13->down = box18;
		box13->left = box12;
		box13->right = box14;

		box14->up = box9;
		box14->down = box19;
		box14->left = box13;
		box14->right = box15;

		box15->up = box10;
		box15->down = box20;
		box15->left = box14;
		box15->right = roster3;

		box16->up = box11;
		box16->down = box21;
		box16->right = box17;

		box17->up = box12;
		box17->down = box22;
		box17->left = box16;
		box17->right = box18;

		box18->up = box13;
		box18->down = box23;
		box18->left = box17;
		box18->right = box19;

		box19->up = box14;
		box19->down = box24;
		box19->left = box18;
		box19->right = box20;

		box20->up = box15;
		box20->down = box25;
		box20->left = box19;
		box20->right = roster3;

		box21->up = box16;
		box21->down = box26;
		box21->right = box22;

		box22->up = box17;
		box22->down = box27;
		box22->left = box21;
		box22->right = box23;

		box23->up = box18;
		box23->down = box28;
		box23->left = box22;
		box23->right = box24;

		box24->up = box19;
		box24->down = box29;
		box24->left = box23;
		box24->right = box25;

		box25->up = box20;
		box25->down = box30;
		box25->left = box24;
		box25->right = roster5;

		box26->up = box21;
		box26->right = box27;

		box27->up = box22;
		box27->left = box26;
		box27->right = box28;

		box28->up = box23;
		box28->left = box27;
		box28->right = box29;

		box29->up = box24;
		box29->left = box28;
		box29->right = box30;

		box30->up = box25;
		box30->left = box29;
		box30->right = roster5;

		roster1->down = roster3;
		roster1->left = box10;
		roster1->right = roster2;

		roster2->down = roster4;
		roster2->left = roster1;

		roster3->up = roster1;
		roster3->down = roster5;
		roster3->left = box15;
		roster3->right = roster4;

		roster4->up = roster2;
		roster4->down = roster6;
		roster4->left = roster3;

		roster5->up = roster3;
		roster5->left = box25;
		roster5->right = roster6;

		roster6->up = roster4;
		roster6->left = roster5;

		leftArrow->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * -2), topLeftBoxY - (boxYGap * -1), boxWidth / 2.0f, boxHeight / 2.0f, Color::WHITE };
		boxTitle->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 0), topLeftBoxY - (boxYGap * -1), boxWidth * 3.0f, boxHeight / 2.0f, Color::WHITE };
		rightArrow->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 2), topLeftBoxY - (boxYGap * -1), boxWidth / 2.0f, boxHeight / 2.0f, Color::WHITE };

		box1->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * -2), topLeftBoxY - (boxYGap * 0), boxWidth, boxHeight, Color::WHITE };
		box2->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * -1), topLeftBoxY - (boxYGap * 0), boxWidth, boxHeight, Color::WHITE };
		box3->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 0), topLeftBoxY - (boxYGap * 0), boxWidth, boxHeight, Color::WHITE };
		box4->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 1), topLeftBoxY - (boxYGap * 0), boxWidth, boxHeight, Color::WHITE };
		box5->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 2), topLeftBoxY - (boxYGap * 0), boxWidth, boxHeight, Color::WHITE };

		box6->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * -2), topLeftBoxY - (boxYGap * 1), boxWidth, boxHeight, Color::WHITE };
		box7->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * -1), topLeftBoxY - (boxYGap * 1), boxWidth, boxHeight, Color::WHITE };
		box8->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 0), topLeftBoxY - (boxYGap * 1), boxWidth, boxHeight, Color::WHITE };
		box9->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 1), topLeftBoxY - (boxYGap * 1), boxWidth, boxHeight, Color::WHITE };
		box10->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 2), topLeftBoxY - (boxYGap * 1), boxWidth, boxHeight, Color::WHITE };

		box11->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * -2), topLeftBoxY - (boxYGap * 2), boxWidth, boxHeight, Color::WHITE };
		box12->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * -1), topLeftBoxY - (boxYGap * 2), boxWidth, boxHeight, Color::WHITE };
		box13->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 0), topLeftBoxY - (boxYGap * 2), boxWidth, boxHeight, Color::WHITE };
		box14->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 1), topLeftBoxY - (boxYGap * 2), boxWidth, boxHeight, Color::WHITE };
		box15->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 2), topLeftBoxY - (boxYGap * 2), boxWidth, boxHeight, Color::WHITE };

		box16->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * -2), topLeftBoxY - (boxYGap * 3), boxWidth, boxHeight, Color::WHITE };
		box17->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * -1), topLeftBoxY - (boxYGap * 3), boxWidth, boxHeight, Color::WHITE };
		box18->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 0), topLeftBoxY - (boxYGap * 3), boxWidth, boxHeight, Color::WHITE };
		box19->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 1), topLeftBoxY - (boxYGap * 3), boxWidth, boxHeight, Color::WHITE };
		box20->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 2), topLeftBoxY - (boxYGap * 3), boxWidth, boxHeight, Color::WHITE };

		box21->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * -2), topLeftBoxY - (boxYGap * 4), boxWidth, boxHeight, Color::WHITE };
		box22->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * -1), topLeftBoxY - (boxYGap * 4), boxWidth, boxHeight, Color::WHITE };
		box23->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 0), topLeftBoxY - (boxYGap * 4), boxWidth, boxHeight, Color::WHITE };
		box24->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 1), topLeftBoxY - (boxYGap * 4), boxWidth, boxHeight, Color::WHITE };
		box25->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 2), topLeftBoxY - (boxYGap * 4), boxWidth, boxHeight, Color::WHITE };

		box26->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * -2), topLeftBoxY - (boxYGap * 5), boxWidth, boxHeight, Color::WHITE };
		box27->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * -1), topLeftBoxY - (boxYGap * 5), boxWidth, boxHeight, Color::WHITE };
		box28->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 0), topLeftBoxY - (boxYGap * 5), boxWidth, boxHeight, Color::WHITE };
		box29->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 1), topLeftBoxY - (boxYGap * 5), boxWidth, boxHeight, Color::WHITE };
		box30->renderData = ButtonRenderData{ topLeftBoxX + (boxXGap * 2), topLeftBoxY - (boxYGap * 5), boxWidth, boxHeight, Color::WHITE };

		roster1->renderData = ButtonRenderData{ rosterLeftBoxX + (boxXGap * 0), rosterLeftBoxY - (boxYGap * 2) - (rosterBoxOffset * 0), boxWidth, boxHeight, Color::WHITE };
		roster2->renderData = ButtonRenderData{ rosterLeftBoxX + (boxXGap * 1), rosterLeftBoxY - (boxYGap * 2) - (rosterBoxOffset * 1), boxWidth, boxHeight, Color::WHITE };
		roster3->renderData = ButtonRenderData{ rosterLeftBoxX + (boxXGap * 0), rosterLeftBoxY - (boxYGap * 3) - (rosterBoxOffset * 0), boxWidth, boxHeight, Color::WHITE };
		roster4->renderData = ButtonRenderData{ rosterLeftBoxX + (boxXGap * 1), rosterLeftBoxY - (boxYGap * 3) - (rosterBoxOffset * 1), boxWidth, boxHeight, Color::WHITE };
		roster5->renderData = ButtonRenderData{ rosterLeftBoxX + (boxXGap * 0), rosterLeftBoxY - (boxYGap * 4) - (rosterBoxOffset * 0), boxWidth, boxHeight, Color::WHITE };
		roster6->renderData = ButtonRenderData{ rosterLeftBoxX + (boxXGap * 1), rosterLeftBoxY - (boxYGap * 4) - (rosterBoxOffset * 1), boxWidth, boxHeight, Color::WHITE };

		usePC.addButton(box1);
		usePC.addButton(box2);
		usePC.addButton(box3);
		usePC.addButton(box4);
		usePC.addButton(box5);
		usePC.addButton(box6);
		usePC.addButton(box7);
		usePC.addButton(box8);
		usePC.addButton(box9);
		usePC.addButton(box10);
		usePC.addButton(box11);
		usePC.addButton(box12);
		usePC.addButton(box13);
		usePC.addButton(box14);
		usePC.addButton(box15);
		usePC.addButton(box16);
		usePC.addButton(box17);
		usePC.addButton(box18);
		usePC.addButton(box19);
		usePC.addButton(box20);
		usePC.addButton(box21);
		usePC.addButton(box22);
		usePC.addButton(box23);
		usePC.addButton(box24);
		usePC.addButton(box25);
		usePC.addButton(box26);
		usePC.addButton(box27);
		usePC.addButton(box28);
		usePC.addButton(box29);
		usePC.addButton(box30);
		usePC.addButton(roster1);
		usePC.addButton(roster2);
		usePC.addButton(roster3);
		usePC.addButton(roster4);
		usePC.addButton(roster5);
		usePC.addButton(roster6);

		usePC.addButton(leftArrow);
		usePC.addButton(rightArrow);
		usePC.addButton(boxTitle);

		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * -2), topLeftBoxY - (boxYGap * 0), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures0.string1 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * -1), topLeftBoxY - (boxYGap * 0), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures0.string2 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 0), topLeftBoxY - (boxYGap * 0), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures0.string3 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 1), topLeftBoxY - (boxYGap * 0), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures0.string4 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 2), topLeftBoxY - (boxYGap * 0), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures0.string5 });

		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * -2), topLeftBoxY - (boxYGap * 1), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures1.string1 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * -1), topLeftBoxY - (boxYGap * 1), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures1.string2 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 0), topLeftBoxY - (boxYGap * 1), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures1.string3 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 1), topLeftBoxY - (boxYGap * 1), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures1.string4 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 2), topLeftBoxY - (boxYGap * 1), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures1.string5 });

		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * -2), topLeftBoxY - (boxYGap * 2), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures2.string1 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * -1), topLeftBoxY - (boxYGap * 2), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures2.string2 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 0), topLeftBoxY - (boxYGap * 2), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures2.string3 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 1), topLeftBoxY - (boxYGap * 2), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures2.string4 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 2), topLeftBoxY - (boxYGap * 2), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures2.string5 });

		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * -2), topLeftBoxY - (boxYGap * 3), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures3.string1 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * -1), topLeftBoxY - (boxYGap * 3), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures3.string2 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 0), topLeftBoxY - (boxYGap * 3), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures3.string3 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 1), topLeftBoxY - (boxYGap * 3), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures3.string4 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 2), topLeftBoxY - (boxYGap * 3), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures3.string5 });

		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * -2), topLeftBoxY - (boxYGap * 4), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures4.string1 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * -1), topLeftBoxY - (boxYGap * 4), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures4.string2 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 0), topLeftBoxY - (boxYGap * 4), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures4.string3 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 1), topLeftBoxY - (boxYGap * 4), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures4.string4 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 2), topLeftBoxY - (boxYGap * 4), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures4.string5 });

		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * -2), topLeftBoxY - (boxYGap * 5), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures5.string1 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * -1), topLeftBoxY - (boxYGap * 5), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures5.string2 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 0), topLeftBoxY - (boxYGap * 5), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures5.string3 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 1), topLeftBoxY - (boxYGap * 5), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures5.string4 });
		usePC.addImage(new ImageRenderData{ topLeftBoxX + (boxXGap * 2), topLeftBoxY - (boxYGap * 5), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->pcTextures5.string5 });


		usePC.addImage(new ImageRenderData{ rosterLeftBoxX + (boxXGap * 0), rosterLeftBoxY - (boxYGap * 2) - (rosterBoxOffset * 0), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->trainerRosterTextures.string1 });
		usePC.addImage(new ImageRenderData{ rosterLeftBoxX + (boxXGap * 1), rosterLeftBoxY - (boxYGap * 2) - (rosterBoxOffset * 1), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->trainerRosterTextures.string2 });
		usePC.addImage(new ImageRenderData{ rosterLeftBoxX + (boxXGap * 0), rosterLeftBoxY - (boxYGap * 3) - (rosterBoxOffset * 0), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->trainerRosterTextures.string3 });
		usePC.addImage(new ImageRenderData{ rosterLeftBoxX + (boxXGap * 1), rosterLeftBoxY - (boxYGap * 3) - (rosterBoxOffset * 1), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->trainerRosterTextures.string4 });
		usePC.addImage(new ImageRenderData{ rosterLeftBoxX + (boxXGap * 0), rosterLeftBoxY - (boxYGap * 4) - (rosterBoxOffset * 0), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->trainerRosterTextures.string5 });
		usePC.addImage(new ImageRenderData{ rosterLeftBoxX + (boxXGap * 1), rosterLeftBoxY - (boxYGap * 4) - (rosterBoxOffset * 1), boxWidth / 2.5f, boxHeight / 2.5f, "", &pcData->trainerRosterTextures.string6 });

		// Move Highlight
		{
			pcData->movePokemonHighlightData.widthPercent = boxWidth / 2.0f;
			pcData->movePokemonHighlightData.heightPercent = boxHeight / 2.0f;
			pcData->movePokemonHighlightData.staticImage = g_overlayTextureLocations[MenuOverlay::POKEDEX_HIGHLIGHT_SORT];
			pcData->movePokemonHighlightData.deleteWithScene = false;
			usePC.addImage(&pcData->movePokemonHighlightData);
		}

		menu->add(MenuScene::USE_PC, usePC);
	}

	// PC Option Selection
	{

		float optionWidth = boxWidth;
		float optionHeight = boxHeight / 4.0f;

		float backgroundShrinkSize = 3.0f;


		Overlay pcOptionSelection(menu->getRenderer());

		//TODO: Probably create a new image for the background for this
		pcData->overlayBackgroundLocation.widthPercent = (optionWidth)-(optionWidth / backgroundShrinkSize);
		pcData->overlayBackgroundLocation.heightPercent = (optionHeight * 4.0f) - ((optionHeight * 4.0f) / backgroundShrinkSize);
		pcData->overlayBackgroundLocation.staticImage = g_overlayTextureLocations[MenuOverlay::DELETE_CONFIRMATION];
		pcData->overlayBackgroundLocation.deleteWithScene = false;
		pcOptionSelection.setOverlayBackground(&pcData->overlayBackgroundLocation);

		Button* moveButton = new Button;
		Button* summaryButton = new Button;
		Button* renameButton = new Button;
		Button* deleteButton = new Button;

		moveButton->text = "MOVE";
		summaryButton->text = "VIEW";
		renameButton->text = "NAME";
		deleteButton->text = "FREE";

		moveButton->data = 0;
		summaryButton->data = 1;
		renameButton->data = 2;
		deleteButton->data = 3;

		moveButton->up = deleteButton;
		moveButton->down = summaryButton;

		summaryButton->up = moveButton;
		summaryButton->down = renameButton;

		renameButton->up = summaryButton;
		renameButton->down = deleteButton;

		deleteButton->up = renameButton;
		deleteButton->down = moveButton;


		pcData->moveButtonData.widthPercent = optionWidth;
		pcData->moveButtonData.heightPercent = optionHeight;

		pcData->summaryButtonData.widthPercent = optionWidth;
		pcData->summaryButtonData.heightPercent = optionHeight;

		pcData->renameButtonData.widthPercent = optionWidth;
		pcData->renameButtonData.heightPercent = optionHeight;

		pcData->deleteButtonData.widthPercent = optionWidth;
		pcData->deleteButtonData.heightPercent = optionHeight;

		moveButton->dynamicRenderData = &pcData->moveButtonData;
		summaryButton->dynamicRenderData = &pcData->summaryButtonData;
		renameButton->dynamicRenderData = &pcData->renameButtonData;
		deleteButton->dynamicRenderData = &pcData->deleteButtonData;

		pcOptionSelection.addButton(moveButton);
		pcOptionSelection.addButton(summaryButton);
		pcOptionSelection.addButton(renameButton);
		pcOptionSelection.addButton(deleteButton);

		menu->add(MenuOverlay::PC_SELECTION, pcOptionSelection);
	}

	// Free Pokemon
	{
		Overlay deleteConfirmation(menu->getRenderer());
		deleteConfirmation.setOverlayBackground(new ImageRenderData{ 50.0f, 50.0f, 20.0f, 35.0f, g_overlayTextureLocations[MenuOverlay::DELETE_CONFIRMATION] });


		TextBox* confirmMessage = new TextBox;
		Button* yes = new Button;
		Button* no = new Button;

		confirmMessage->dynamic_text = &pcData->freePokemonMessage;
		yes->text = "YES";
		no->text = "NO";

		yes->right = no;
		no->left = yes;


		yes->data = 0;
		no->data = 1;


		confirmMessage->renderData = TextBoxRenderData{ 50.0f, 35.0f, 5.0f };
		yes->renderData = ButtonRenderData{ 45.0f, 25.0f, 10.0f, 7.5f, Color::WHITE };
		no->renderData = ButtonRenderData{ 55.0f, 25.0f, 10.0f, 7.5f, Color::WHITE };

		deleteConfirmation.addButton(no);
		deleteConfirmation.addButton(yes);
		deleteConfirmation.addTextBox(confirmMessage);

		float frameScale = 1.0f;
		float pokemonImageScale = frameScale + 0.2f;

		deleteConfirmation.addImage(new ImageRenderData{ 50.0f, 65.0f, (9.0f / frameScale), (16.0f / frameScale), g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });
		deleteConfirmation.addImage(new ImageRenderData{ 50.0f, 65.0f, (9.0f / pokemonImageScale), (16.0f / pokemonImageScale), "", &pcData->selectedPokemonTexture });

		menu->add(MenuOverlay::FREE_POKEMON_CONFIRMATION, deleteConfirmation);
	}

	// Rename Pokemon
	{
		Scene renamePokemon(menu->getRenderer());
		renamePokemon.setBackgroundPath(g_sceneTextureLocations[MenuScene::SET_PLAYER_NAME]);

		TextBox* playerNameText = new TextBox;
		playerNameText->text = "RENAME POKEMON";
		playerNameText->renderData = TextBoxRenderData{ 50.0f, 83.0f, 10.0f };
		renamePokemon.addTextBox(playerNameText);

		float xPos = 5.0f;
		float yPos = 92.5f;

		float dimensionScale = 2.3f;
		float width = 9.0f / dimensionScale;
		float height = 16.0f / dimensionScale;
		float pokemonDiff = 0.8f;

		renamePokemon.addImage(new ImageRenderData{ xPos, yPos, width, height, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });
		renamePokemon.addImage(new ImageRenderData{ xPos, yPos, width - pokemonDiff, height - pokemonDiff, "", &pcData->selectedPokemonTexture });

		menu->add(MenuScene::RENAME_POKEMON, renamePokemon);
	}
}

void MenuSetup::setupSummaryData(Menu* menu, SummaryData* data)
{
	Scene pokemonSummary(menu->getRenderer());
	pokemonSummary.setBackgroundPath(g_sceneTextureLocations[MenuScene::POKEMON_SUMMARY]);

	float titleFontSize = 8.0f;
	float dataFontSize = 4.0f;

	float pokemonNameY = 85.0f;

	// Pokemon Name
	{
		TextBox* pokemonName = new TextBox;
		pokemonName->text = data->moveData.pokemonName;
		pokemonName->renderData = TextBoxRenderData{ 50.0f, pokemonNameY, titleFontSize };

		pokemonSummary.addTextBox(pokemonName);
	}

	// Pokemon Stats
	{
		float dataXLeft = 0.5f;
		float dataXRight = 30.0f;
		float dataYStart = pokemonNameY - 20.0f;
		float dataOffset = dataFontSize + 2.0f;

		TextBox* statsTitle = new TextBox;

		TextBox* level = new TextBox;
		TextBox* health = new TextBox;
		TextBox* attack = new TextBox;
		TextBox* defense = new TextBox;
		TextBox* spAttack = new TextBox;
		TextBox* spDefense = new TextBox;
		TextBox* speed = new TextBox;


		TextBox* levelStat = new TextBox;
		TextBox* healthStat = new TextBox;
		TextBox* attackStat = new TextBox;
		TextBox* defenseStat = new TextBox;
		TextBox* spAttackStat = new TextBox;
		TextBox* spDefenseStat = new TextBox;
		TextBox* speedStat = new TextBox;

		statsTitle->text = "STATS";


		level->text = "LEVEL:";
		health->text = "HP:";
		attack->text = "ATTACK:";
		defense->text = "DEFENSE:";
		spAttack->text = "SP.ATK:";
		spDefense->text = "SP.DEF:";
		speed->text = "SPEED:";

		levelStat->text = data->statsData.level;
		healthStat->text = data->statsData.health;
		attackStat->text = data->statsData.attack;
		defenseStat->text = data->statsData.defense;
		spAttackStat->text = data->statsData.spAttack;
		spDefenseStat->text = data->statsData.spDefense;
		speedStat->text = data->statsData.speed;

		statsTitle->renderData = TextBoxRenderData{ dataXRight / 2.0f, dataYStart + dataOffset, titleFontSize };

		level->renderData = TextBoxRenderData{ dataXLeft, dataYStart - (dataOffset * 0), dataFontSize, Color::BLACK, Alignment::LEFT_ALIGN };
		health->renderData = TextBoxRenderData{ dataXLeft, dataYStart - (dataOffset * 1), dataFontSize, Color::BLACK, Alignment::LEFT_ALIGN };
		attack->renderData = TextBoxRenderData{ dataXLeft, dataYStart - (dataOffset * 2), dataFontSize, Color::BLACK, Alignment::LEFT_ALIGN };
		defense->renderData = TextBoxRenderData{ dataXLeft, dataYStart - (dataOffset * 3), dataFontSize, Color::BLACK, Alignment::LEFT_ALIGN };
		spAttack->renderData = TextBoxRenderData{ dataXLeft, dataYStart - (dataOffset * 4), dataFontSize, Color::BLACK, Alignment::LEFT_ALIGN };
		spDefense->renderData = TextBoxRenderData{ dataXLeft, dataYStart - (dataOffset * 5), dataFontSize, Color::BLACK, Alignment::LEFT_ALIGN };
		speed->renderData = TextBoxRenderData{ dataXLeft, dataYStart - (dataOffset * 6), dataFontSize, Color::BLACK, Alignment::LEFT_ALIGN };

		levelStat->renderData = TextBoxRenderData{ dataXRight, dataYStart - (dataOffset * 0), dataFontSize, Color::BLACK, Alignment::RIGHT_ALIGN };
		healthStat->renderData = TextBoxRenderData{ dataXRight, dataYStart - (dataOffset * 1), dataFontSize, Color::BLACK, Alignment::RIGHT_ALIGN };
		attackStat->renderData = TextBoxRenderData{ dataXRight, dataYStart - (dataOffset * 2), dataFontSize, Color::BLACK, Alignment::RIGHT_ALIGN };
		defenseStat->renderData = TextBoxRenderData{ dataXRight, dataYStart - (dataOffset * 3), dataFontSize, Color::BLACK, Alignment::RIGHT_ALIGN };
		spAttackStat->renderData = TextBoxRenderData{ dataXRight, dataYStart - (dataOffset * 4), dataFontSize, Color::BLACK, Alignment::RIGHT_ALIGN };
		spDefenseStat->renderData = TextBoxRenderData{ dataXRight, dataYStart - (dataOffset * 5), dataFontSize, Color::BLACK, Alignment::RIGHT_ALIGN };
		speedStat->renderData = TextBoxRenderData{ dataXRight, dataYStart - (dataOffset * 6), dataFontSize, Color::BLACK, Alignment::RIGHT_ALIGN };

		pokemonSummary.addTextBox(level);
		pokemonSummary.addTextBox(health);
		pokemonSummary.addTextBox(attack);
		pokemonSummary.addTextBox(defense);
		pokemonSummary.addTextBox(spAttack);
		pokemonSummary.addTextBox(spDefense);
		pokemonSummary.addTextBox(speed);


		pokemonSummary.addTextBox(statsTitle);
		pokemonSummary.addTextBox(levelStat);
		pokemonSummary.addTextBox(healthStat);
		pokemonSummary.addTextBox(attackStat);
		pokemonSummary.addTextBox(defenseStat);
		pokemonSummary.addTextBox(spAttackStat);
		pokemonSummary.addTextBox(spDefenseStat);
		pokemonSummary.addTextBox(speedStat);

	}

	// Pokemon Images
	{
		float borderSize = 1.2f;
		float pokemonSize = borderSize + 0.2f;

		float pokemonImageY = 70.0f;
		float borderHeight = 16.0f / borderSize;

		pokemonSummary.addImage(new ImageRenderData{ 50.0f, pokemonImageY, 9.0f / borderSize, borderHeight, g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME] });
		pokemonSummary.addImage(new ImageRenderData{ 50.0f, pokemonImageY, 9.0f / pokemonSize, 16.0f / pokemonSize, data->moveData.pokemonImageTextureLocation });

		data->type1.percentageY = pokemonImageY - borderHeight - data->type1.heightPercent - 1.0f;
		data->type2.percentageY = pokemonImageY - borderHeight - data->type2.heightPercent - 1.0f;

		pokemonSummary.addImage(&data->type1);
		pokemonSummary.addImage(&data->type2);

	}

	// Move Stats
	{
		TextBox* power = new TextBox;
		TextBox* powerData = new TextBox;

		TextBox* accuracy = new TextBox;
		TextBox* accuracyData = new TextBox;

		TextBox* description = new TextBox;

		power->text = "POWER";
		powerData->dynamic_text = &data->moveData.power;

		accuracy->text = "ACCURACY";
		accuracyData->dynamic_text = &data->moveData.accuracy;

		description->dynamic_text = &data->moveData.description;

		float xCenter = 84.8f;

		power->renderData = TextBoxRenderData{ xCenter, (510.0f / 563.0f) * 100.0f, 2.5f };
		powerData->renderData = TextBoxRenderData{ xCenter, (479.0f / 563.0f) * 100.0f, 2.5f };
		accuracy->renderData = TextBoxRenderData{ xCenter, (414.0f / 563.0f) * 100.0f, 2.5f };
		accuracyData->renderData = TextBoxRenderData{ xCenter, (383.0f / 563.0f) * 100.0f, 2.5f };
		description->renderData = TextBoxRenderData{ (764.0f / 1000.0f) * 100.0f, (317.0f / 563.0f) * 100.0f, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN, 16.0f, 1.25f };

		pokemonSummary.addTextBox(power);
		pokemonSummary.addTextBox(powerData);
		pokemonSummary.addTextBox(accuracy);
		pokemonSummary.addTextBox(accuracyData);
		pokemonSummary.addTextBox(description);
	}

	// Move Buttons
	{
		float baseX = 60.0f;
		float xButtonGap = 22.8f;
		float baseY = 55.0f;

		float buttonXPercent = 15.78f;
		float buttonYPercent = 8.9f;



		float moveNameX = (baseX / 1000.0f) * 100.0f;
		float moveCurPPX = ((baseX + 135.0f) / 1000.0f) * 100.0f;
		float moveMaxPPX = ((baseX + 150.0f) / 1000.0f) * 100.0f;
		float moveTypeX = ((baseX + 30.0f) / 1000.0f) * 100.0f;


		float moveNameY = (baseY / 563.0f) * 100.0f;
		float moveCurPPY = ((baseY - 43.0f) / 563.0f) * 100.0f;
		float moveMaxPPY = ((baseY - 43.0f) / 563.0f) * 100.0f;
		float moveTypeY = ((baseY - 20.0f) / 563.0f) * 100.0f;

		TextBox* move1Name = new TextBox();
		TextBox* move2Name = new TextBox();
		TextBox* move3Name = new TextBox();
		TextBox* move4Name = new TextBox();

		TextBox* currentPP1 = new TextBox();
		TextBox* currentPP2 = new TextBox();
		TextBox* currentPP3 = new TextBox();
		TextBox* currentPP4 = new TextBox();

		TextBox* maxPP1 = new TextBox();
		TextBox* maxPP2 = new TextBox();
		TextBox* maxPP3 = new TextBox();
		TextBox* maxPP4 = new TextBox();

		move1Name->text = data->moveData.move1.moveName;
		move2Name->text = data->moveData.move2.moveName;
		move3Name->text = data->moveData.move3.moveName;
		move4Name->text = data->moveData.move4.moveName;

		currentPP1->text = data->moveData.move1.currentPP;
		currentPP2->text = data->moveData.move2.currentPP;
		currentPP3->text = data->moveData.move3.currentPP;
		currentPP4->text = data->moveData.move4.currentPP;

		maxPP1->text = data->moveData.move1.maxPP;
		maxPP2->text = data->moveData.move2.maxPP;
		maxPP3->text = data->moveData.move3.maxPP;
		maxPP4->text = data->moveData.move4.maxPP;

		move1Name->renderData = TextBoxRenderData{ moveNameX + (xButtonGap * 0), moveNameY, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		move2Name->renderData = TextBoxRenderData{ moveNameX + (xButtonGap * 1), moveNameY, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		move3Name->renderData = TextBoxRenderData{ moveNameX + (xButtonGap * 2), moveNameY, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		move4Name->renderData = TextBoxRenderData{ moveNameX + (xButtonGap * 3), moveNameY, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };

		currentPP1->renderData = TextBoxRenderData{ moveCurPPX + (xButtonGap * 0), moveCurPPY, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		currentPP2->renderData = TextBoxRenderData{ moveCurPPX + (xButtonGap * 1), moveCurPPY, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		currentPP3->renderData = TextBoxRenderData{ moveCurPPX + (xButtonGap * 2), moveCurPPY, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
		currentPP4->renderData = TextBoxRenderData{ moveCurPPX + (xButtonGap * 3), moveCurPPY, 4.0f, Color::BLACK, Alignment::RIGHT_ALIGN };

		maxPP1->renderData = TextBoxRenderData{ moveMaxPPX + (xButtonGap * 0), moveMaxPPY, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		maxPP2->renderData = TextBoxRenderData{ moveMaxPPX + (xButtonGap * 1), moveMaxPPY, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		maxPP3->renderData = TextBoxRenderData{ moveMaxPPX + (xButtonGap * 2), moveMaxPPY, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		maxPP4->renderData = TextBoxRenderData{ moveMaxPPX + (xButtonGap * 3), moveMaxPPY, 4.0f, Color::BLACK, Alignment::LEFT_ALIGN };


		pokemonSummary.addImage(new ImageRenderData{ moveTypeX + (xButtonGap * 0), moveTypeY, 3.0f, 1.5f,data->moveData.move1.moveTypeTextureLocation });
		pokemonSummary.addImage(new ImageRenderData{ moveTypeX + (xButtonGap * 1), moveTypeY, 3.0f, 1.5f,data->moveData.move2.moveTypeTextureLocation });
		pokemonSummary.addImage(new ImageRenderData{ moveTypeX + (xButtonGap * 2), moveTypeY, 3.0f, 1.5f,data->moveData.move3.moveTypeTextureLocation });
		pokemonSummary.addImage(new ImageRenderData{ moveTypeX + (xButtonGap * 3), moveTypeY, 3.0f, 1.5f, data->moveData.move4.moveTypeTextureLocation });

		pokemonSummary.addTextBox(move1Name);
		pokemonSummary.addTextBox(move2Name);
		pokemonSummary.addTextBox(move3Name);
		pokemonSummary.addTextBox(move4Name);

		pokemonSummary.addTextBox(currentPP1);
		pokemonSummary.addTextBox(currentPP2);
		pokemonSummary.addTextBox(currentPP3);
		pokemonSummary.addTextBox(currentPP4);

		pokemonSummary.addTextBox(maxPP1);
		pokemonSummary.addTextBox(maxPP2);
		pokemonSummary.addTextBox(maxPP3);
		pokemonSummary.addTextBox(maxPP4);



		pokemonSummary.addImage(new ImageRenderData{ buttonXPercent + (xButtonGap * 0), buttonYPercent,  (113.0f / 1000.0f) * 100.0f, (50.0f / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::MOVE_OUTLINE], nullptr, &data->moveData.move1OutlineVisiblity });	//Move 1
		pokemonSummary.addImage(new ImageRenderData{ buttonXPercent + (xButtonGap * 1), buttonYPercent,  (113.0f / 1000.0f) * 100.0f, (50.0f / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::MOVE_OUTLINE], nullptr, &data->moveData.move2OutlineVisiblity });	//Move 2
		pokemonSummary.addImage(new ImageRenderData{ buttonXPercent + (xButtonGap * 2), buttonYPercent,  (113.0f / 1000.0f) * 100.0f, (50.0f / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::MOVE_OUTLINE], nullptr, &data->moveData.move3OutlineVisiblity });	//Move 3
		pokemonSummary.addImage(new ImageRenderData{ buttonXPercent + (xButtonGap * 3), buttonYPercent,  (113.0f / 1000.0f) * 100.0f, (50.0f / 563.0f) * 100.0f, g_overlayTextureLocations[MenuOverlay::MOVE_OUTLINE], nullptr, &data->moveData.move4OutlineVisiblity });		//Move 4



		Button* move1Button = new Button;
		Button* move2Button = new Button;
		Button* move3Button = new Button;
		Button* move4Button = new Button;

		move1Button->right = move2Button;
		move1Button->left = move4Button;

		move2Button->right = move3Button;
		move2Button->left = move1Button;

		move3Button->right = move4Button;
		move3Button->left = move2Button;

		move4Button->right = move1Button;
		move4Button->left = move3Button;

		move1Button->renderData = ButtonRenderData{ 0,0,0,0, Color::TRANSPARENT, 0,&data->moveData.buttonVisibility };
		move2Button->renderData = ButtonRenderData{ 0,0,0,0, Color::TRANSPARENT, 0,&data->moveData.buttonVisibility };
		move3Button->renderData = ButtonRenderData{ 0,0,0,0, Color::TRANSPARENT, 0,&data->moveData.buttonVisibility };
		move4Button->renderData = ButtonRenderData{ 0,0,0,0, Color::TRANSPARENT, 0,&data->moveData.buttonVisibility };

		pokemonSummary.addButton(move1Button);
		pokemonSummary.addButton(move2Button);
		pokemonSummary.addButton(move3Button);
		pokemonSummary.addButton(move4Button);
	}

	// EV Stat Graph
	{
		TextBox* graphHP = new TextBox;
		TextBox* graphAttack = new TextBox;
		TextBox* graphDefense = new TextBox;
		TextBox* graphSpeed = new TextBox;
		TextBox* graphSPAttack = new TextBox;
		TextBox* graphSPDefense = new TextBox;


		graphHP->text = data->hpStatGraphData.value;
		graphAttack->text = data->attackStatGraphData.value;
		graphDefense->text = data->defenseStatGraphData.value;
		graphSpeed->text = data->speedStatGraphData.value;
		graphSPAttack->text = data->spAttackStatGraphData.value;
		graphSPDefense->text = data->spDefStatGraphData.value;


		graphHP->dynamicRenderData = &data->hpStatGraphData.renderData;
		graphAttack->dynamicRenderData = &data->attackStatGraphData.renderData;
		graphDefense->dynamicRenderData = &data->defenseStatGraphData.renderData;
		graphSpeed->dynamicRenderData = &data->speedStatGraphData.renderData;
		graphSPAttack->dynamicRenderData = &data->spAttackStatGraphData.renderData;
		graphSPDefense->dynamicRenderData = &data->spDefStatGraphData.renderData;


		pokemonSummary.addTextBox(graphHP);
		pokemonSummary.addTextBox(graphAttack);
		pokemonSummary.addTextBox(graphDefense);
		pokemonSummary.addTextBox(graphSpeed);
		pokemonSummary.addTextBox(graphSPAttack);
		pokemonSummary.addTextBox(graphSPDefense);


		pokemonSummary.addPolygon(&data->evStatContainerOutline);
		pokemonSummary.addPolygon(&data->evStatContainer);
		pokemonSummary.addPolygon(&data->evStatGraph);
	}

	menu->add(MenuScene::POKEMON_SUMMARY, pokemonSummary);
}

void MenuSetup::setupSaveAndExit(Menu* menu)
{
	Overlay saveAndExit{ menu->getRenderer()};

	saveAndExit.setOverlayBackground(new ImageRenderData{ 50.0f, 50.0f, 30.0f, 30.0f, g_overlayTextureLocations[MenuOverlay::DELETE_CONFIRMATION] });


	TextBox* confirmMessage = new TextBox;
	Button* yes = new Button;
	Button* no = new Button;

	confirmMessage->text = "Save Game?";
	yes->text = "YES";
	no->text = "NO";

	yes->right = no;
	no->left = yes;


	yes->data = (int)true;
	no->data = (int)false;

	confirmMessage->renderData = TextBoxRenderData{ 50.0f, 55.0f, 5.0f };
	yes->renderData = ButtonRenderData{ 45.0f, 45.0f, 10.0f, 7.5f };
	no->renderData = ButtonRenderData{ 55.0f, 45.0f, 10.0f, 7.5f };

	saveAndExit.addTextBox(confirmMessage);
	saveAndExit.addButton(no);
	saveAndExit.addButton(yes);

	menu->add(MenuOverlay::SAVE_BEFORE_EXIT, saveAndExit);
}

void MenuSetup::setupSelectPlayerGender(Menu* menu, bool* boyHighlight, bool* girlHighlight)
{
	Scene selectPlayerGender(menu->getRenderer());

	Button* girl = new Button();
	Button* boy = new Button();

	girl->right = boy;
	boy->left = girl;

	girl->data = 0;
	boy->data = 1;

	selectPlayerGender.addButton(girl);
	selectPlayerGender.addButton(boy);

	selectPlayerGender.addImage(new ImageRenderData{ 50.0f,50.0f,50.0f,50.0f, g_overlayTextureLocations[MenuOverlay::SELECT_PLAYER_GENDER_FEMALE], nullptr, girlHighlight });
	selectPlayerGender.addImage(new ImageRenderData{ 50.0f,50.0f,50.0f,50.0f, g_overlayTextureLocations[MenuOverlay::SELECT_PLAYER_GENDER_MALE], nullptr, boyHighlight });

	menu->add(MenuScene::SELECT_PLAYER_GENDER, selectPlayerGender);
}

void MenuSetup::setupPlayerAcqiuresItem(Menu* menu, AcquireItemData* data)
{
	Overlay acquireItemNotification{ menu->getRenderer()};
	acquireItemNotification.setOverlayBackground(new ImageRenderData{ 50.0f, 50.0f, 20.0f, 30.0f, g_overlayTextureLocations[MenuOverlay::DELETE_CONFIRMATION] });

	TextBox* itemAquired = new TextBox;

	itemAquired->text = "Got " + data->itemName + "!";

	Button* nextButton = new Button;
	nextButton->data = 0;
	nextButton->dynamic_text = &data->buttonText;

	nextButton->renderData = ButtonRenderData{ 50.0f, 30.0f, 10.0f, 7.5f };
	itemAquired->renderData = TextBoxRenderData{ 50.0f, 60.0f, 5.0f };

	acquireItemNotification.addButton(nextButton);
	acquireItemNotification.addTextBox(itemAquired);

	float imageSize = 0.5f;

	float width = imageSize * 9.0f;
	float height = imageSize * 16.0f;

	acquireItemNotification.addImage(new ImageRenderData{ 50.0f, 50.0f, width, height, data->itemLocation });

	menu->add(MenuOverlay::PLAYER_ACQUIRE_ITEM, acquireItemNotification);
}

void MenuSetup::setupProfTablePokemonSelection(Menu* menu, SelectProfPokemonData* data)
{
	Overlay getFirstPokemon{ menu->getRenderer()};

	TextBox* pokemonName = new TextBox;
	TextBox* pokemonDescription = new TextBox;

	float xPos = 50.0f;
	float yPos = 70.0f;

	float boxSize = 3.0f;

	float width = (3.0f * 9.0f) * 3.0f;
	float height = (3.0f * 16.0f) * 1.0f;

	float imageSize = 5.0f;
	float frameSize = 4.0f;
	float pokemonSize = frameSize + 0.4f;
	// Background
	//getFirstPokemon.addImage(new ImageRenderData{xPos, yPos, width / 2.0f, height / 2.0f, data->backgroundPath});

	pokemonName->dynamic_text = &data->pokemonName;
	pokemonDescription->dynamic_text = &data->pokemonDescription;

	pokemonName->renderData = TextBoxRenderData{ xPos, 0.0f, 3.0f };
	pokemonDescription->renderData = TextBoxRenderData{ xPos, 0.0f, 3.0f };

	float imageWidth = 9.0f / imageSize;
	float imageHeight = 16.0f / imageSize;

	float frameWidth = 9.0f / frameSize;
	float frameHeight = 16.0f / frameSize;

	float pokemonWidth = 9.0f / pokemonSize;
	float pokemonHeight = 16.0f / pokemonSize;

	float pokeballIncrease = 0.0f;
	float pokemonIncrease = 8.0f;
	float widthDifference = 5.0f;

	// Pokeballs
	getFirstPokemon.addImage(new ImageRenderData{ xPos - widthDifference, yPos, imageWidth, imageHeight, data->pokeball, nullptr, &data->leftPokemonVisible });
	getFirstPokemon.addImage(new ImageRenderData{ xPos, yPos, imageWidth, imageHeight, data->pokeball, nullptr, &data->centerPokemonVisible });
	getFirstPokemon.addImage(new ImageRenderData{ xPos + widthDifference, yPos, imageWidth, imageHeight, data->pokeball, nullptr, &data->rightPokemonVisible });

	// Image Frames
	getFirstPokemon.addImage(new ImageRenderData{ xPos - widthDifference, yPos + pokemonIncrease, frameWidth, frameHeight,"" ,&data->frameImageLeft, &data->leftPokemonVisible });
	getFirstPokemon.addImage(new ImageRenderData{ xPos, yPos + pokemonIncrease, frameWidth, frameHeight, "", &data->frameImageCenter, &data->centerPokemonVisible });
	getFirstPokemon.addImage(new ImageRenderData{ xPos + widthDifference, yPos + pokemonIncrease, frameWidth, frameHeight,"", &data->frameImageRight, &data->rightPokemonVisible });

	// Main Pokemon
	getFirstPokemon.addImage(new ImageRenderData{ xPos - widthDifference, yPos + pokemonIncrease, pokemonWidth, pokemonHeight, data->leftPokemonImage, nullptr, &data->leftPokemonVisible });
	getFirstPokemon.addImage(new ImageRenderData{ xPos, yPos + pokemonIncrease, pokemonWidth, pokemonHeight, data->pokemonImage, nullptr, &data->centerPokemonVisible });
	getFirstPokemon.addImage(new ImageRenderData{ xPos + widthDifference, yPos + pokemonIncrease, pokemonWidth, pokemonHeight, data->rightPokemonImage, nullptr, &data->rightPokemonVisible });


	Button* centerPokemon = new Button;
	Button* leftPokemon = new Button;
	Button* rightPokemon = new Button;

	centerPokemon->data = 0;
	leftPokemon->data = 1;
	rightPokemon->data = 2;

	centerPokemon->right = rightPokemon;
	centerPokemon->left = leftPokemon;

	leftPokemon->right = centerPokemon;
	leftPokemon->left = rightPokemon;

	rightPokemon->left = centerPokemon;
	rightPokemon->right = leftPokemon;

	centerPokemon->renderData = ButtonRenderData{ 0.0f,0.0f,0.0f,0.0f, Color::RED, 0, &data->buttonsVisible };
	leftPokemon->renderData = ButtonRenderData{ 0.0f,0.0f,0.0f,0.0f, Color::RED, 0, &data->buttonsVisible };
	rightPokemon->renderData = ButtonRenderData{ 0.0f,0.0f,0.0f,0.0f, Color::RED, 0, &data->buttonsVisible };

	getFirstPokemon.addButton(centerPokemon);
	getFirstPokemon.addButton(leftPokemon);
	getFirstPokemon.addButton(rightPokemon);

	getFirstPokemon.addTextBox(pokemonName);
	getFirstPokemon.addTextBox(pokemonDescription);


	// Dialogue
	{
		getFirstPokemon.addImage(new ImageRenderData{ 50.0f, 12.5f, 50.0f, 10.0f, g_overlayTextureLocations[MenuOverlay::DIALOGUE], nullptr, &data->dialogueVisible });

		TextBox* topLine = new TextBox;
		TextBox* botLine = new TextBox;

		topLine->dynamic_text = &data->topLine;
		botLine->dynamic_text = &data->botLine;

		topLine->renderData = TextBoxRenderData{ 4.0f, 12.0f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };
		botLine->renderData = TextBoxRenderData{ 4.0f, 4.0f, 5.0f, Color::BLACK, Alignment::LEFT_ALIGN };

		getFirstPokemon.addTextBox(topLine);
		getFirstPokemon.addTextBox(botLine);
	}

	menu->add(MenuOverlay::SELECT_POKEMON_FROM_PROFESSOR, getFirstPokemon);
}

void MenuSetup::setupBuyItems(Menu* menu, BuyItemData* data)
{
	// Buy Item Scene
	Scene buyItemScreem(menu->getRenderer());

	// Background
	buyItemScreem.addImage(new ImageRenderData{ 50.0f, 50.0f, 50.0f, 50.0f, "", &data->background });

	TextBox* playerBalance = new TextBox();
	playerBalance->dynamic_text = &data->playerBalance;
	playerBalance->renderData = TextBoxRenderData{ (14.5f / 128.0f) * 100.0f, (57.0f / 72.0f) * 100.0f, 4.0f };
	buyItemScreem.addTextBox(playerBalance);

	// Buttons
	{
		Button* upArrow = new Button;
		Button* item1 = new Button;
		Button* item2 = new Button;
		Button* item3 = new Button;
		Button* item4 = new Button;
		Button* item5 = new Button;
		Button* item6 = new Button;
		Button* downArrow = new Button;

		upArrow->data = arrowDirections::UP;
		downArrow->data = arrowDirections::DOWN;

		item1->data = 0;
		item2->data = 1;
		item3->data = 2;
		item4->data = 3;
		item5->data = 4;
		item6->data = 5;

		upArrow->up = downArrow;
		upArrow->down = item1;

		item1->up = upArrow;
		item1->down = item2;

		item2->up = item1;
		item2->down = item3;

		item3->up = item2;
		item3->down = item4;

		item4->up = item3;
		item4->down = item5;

		item5->up = item4;
		item5->down = item6;

		item6->up = item5;
		item6->down = downArrow;

		downArrow->up = item6;
		downArrow->down = upArrow;

		upArrow->renderData = ButtonRenderData{ 0.0f,0.0f,0.0f,0.0f,Color::BLACK, 0, &data->buttonVisibility };
		item1->renderData = ButtonRenderData{ 0.0f,0.0f,0.0f,0.0f,Color::BLACK, 0, &data->buttonVisibility };
		item2->renderData = ButtonRenderData{ 0.0f,0.0f,0.0f,0.0f,Color::BLACK, 0, &data->buttonVisibility };
		item3->renderData = ButtonRenderData{ 0.0f,0.0f,0.0f,0.0f,Color::BLACK, 0, &data->buttonVisibility };
		item4->renderData = ButtonRenderData{ 0.0f,0.0f,0.0f,0.0f,Color::BLACK, 0, &data->buttonVisibility };
		item5->renderData = ButtonRenderData{ 0.0f,0.0f,0.0f,0.0f,Color::BLACK, 0, &data->buttonVisibility };
		item6->renderData = ButtonRenderData{ 0.0f,0.0f,0.0f,0.0f,Color::BLACK, 0, &data->buttonVisibility };
		downArrow->renderData = ButtonRenderData{ 0.0f,0.0f,0.0f,0.0f,Color::BLACK, 0, &data->buttonVisibility };

		buyItemScreem.addButton(upArrow);
		buyItemScreem.addButton(item1);
		buyItemScreem.addButton(item2);
		buyItemScreem.addButton(item3);
		buyItemScreem.addButton(item4);
		buyItemScreem.addButton(item5);
		buyItemScreem.addButton(item6);
		buyItemScreem.addButton(downArrow);
	}

	// Items
	{
		float topX = (84.0f / 128.0f) * 100.0f;
		float costX = (123.0f / 128.0f) * 100.0f;
		float imageX = (79.5f / 128.0f) * 100.0f;

		float topY = (59.5f / 72.0f) * 100.0f;

		float buttonYGap = (6.0f / 72.0f) * 100.0f;

		float fontSize = 3.0f;
		Color textColor = Color::BLACK;
		Alignment nameAlignment = Alignment::LEFT_ALIGN;
		Alignment costAlignment = Alignment::RIGHT_ALIGN;

		float imageSize = 7.5f;

		// Item Names
		{
			TextBox* item1Name = new TextBox();
			TextBox* item2Name = new TextBox();
			TextBox* item3Name = new TextBox();
			TextBox* item4Name = new TextBox();
			TextBox* item5Name = new TextBox();
			TextBox* item6Name = new TextBox();

			item1Name->dynamic_text = &data->itemName.string1;
			item2Name->dynamic_text = &data->itemName.string2;
			item3Name->dynamic_text = &data->itemName.string3;
			item4Name->dynamic_text = &data->itemName.string4;
			item5Name->dynamic_text = &data->itemName.string5;
			item6Name->dynamic_text = &data->itemName.string6;

			item1Name->renderData = TextBoxRenderData{ topX, topY - (buttonYGap * 0), fontSize, textColor, nameAlignment };
			item2Name->renderData = TextBoxRenderData{ topX, topY - (buttonYGap * 1), fontSize, textColor, nameAlignment };
			item3Name->renderData = TextBoxRenderData{ topX, topY - (buttonYGap * 2), fontSize, textColor, nameAlignment };
			item4Name->renderData = TextBoxRenderData{ topX, topY - (buttonYGap * 3), fontSize, textColor, nameAlignment };
			item5Name->renderData = TextBoxRenderData{ topX, topY - (buttonYGap * 4), fontSize, textColor, nameAlignment };
			item6Name->renderData = TextBoxRenderData{ topX, topY - (buttonYGap * 5), fontSize, textColor, nameAlignment };

			buyItemScreem.addTextBox(item1Name);
			buyItemScreem.addTextBox(item2Name);
			buyItemScreem.addTextBox(item3Name);
			buyItemScreem.addTextBox(item4Name);
			buyItemScreem.addTextBox(item5Name);
			buyItemScreem.addTextBox(item6Name);
		}

		// Item Costs
		{
			TextBox* item1Cost = new TextBox();
			TextBox* item2Cost = new TextBox();
			TextBox* item3Cost = new TextBox();
			TextBox* item4Cost = new TextBox();
			TextBox* item5Cost = new TextBox();
			TextBox* item6Cost = new TextBox();

			item1Cost->dynamic_text = &data->itemCost.string1;
			item2Cost->dynamic_text = &data->itemCost.string2;
			item3Cost->dynamic_text = &data->itemCost.string3;
			item4Cost->dynamic_text = &data->itemCost.string4;
			item5Cost->dynamic_text = &data->itemCost.string5;
			item6Cost->dynamic_text = &data->itemCost.string6;

			item1Cost->renderData = TextBoxRenderData{ costX, topY - (buttonYGap * 0), fontSize, textColor, costAlignment };
			item2Cost->renderData = TextBoxRenderData{ costX, topY - (buttonYGap * 1), fontSize, textColor, costAlignment };
			item3Cost->renderData = TextBoxRenderData{ costX, topY - (buttonYGap * 2), fontSize, textColor, costAlignment };
			item4Cost->renderData = TextBoxRenderData{ costX, topY - (buttonYGap * 3), fontSize, textColor, costAlignment };
			item5Cost->renderData = TextBoxRenderData{ costX, topY - (buttonYGap * 4), fontSize, textColor, costAlignment };
			item6Cost->renderData = TextBoxRenderData{ costX, topY - (buttonYGap * 5), fontSize, textColor, costAlignment };

			buyItemScreem.addTextBox(item1Cost);
			buyItemScreem.addTextBox(item2Cost);
			buyItemScreem.addTextBox(item3Cost);
			buyItemScreem.addTextBox(item4Cost);
			buyItemScreem.addTextBox(item5Cost);
			buyItemScreem.addTextBox(item6Cost);
		}

		// Item Images
		{
			float width = 9.0f / imageSize;
			float height = 16.0f / imageSize;
			buyItemScreem.addImage(new ImageRenderData{ imageX, topY - (buttonYGap * 0) + (buttonYGap / 3.0f), width, height, "", &data->itemTexture.string1 });
			buyItemScreem.addImage(new ImageRenderData{ imageX, topY - (buttonYGap * 1) + (buttonYGap / 3.0f), width, height, "", &data->itemTexture.string2 });
			buyItemScreem.addImage(new ImageRenderData{ imageX, topY - (buttonYGap * 2) + (buttonYGap / 3.0f), width, height, "", &data->itemTexture.string3 });
			buyItemScreem.addImage(new ImageRenderData{ imageX, topY - (buttonYGap * 3) + (buttonYGap / 3.0f), width, height, "", &data->itemTexture.string4 });
			buyItemScreem.addImage(new ImageRenderData{ imageX, topY - (buttonYGap * 4) + (buttonYGap / 3.0f), width, height, "", &data->itemTexture.string5 });
			buyItemScreem.addImage(new ImageRenderData{ imageX, topY - (buttonYGap * 5) + (buttonYGap / 3.0f), width, height, "", &data->itemTexture.string6 });
		}

	}

	menu->add(MenuScene::BUY_ITEMS, buyItemScreem);
}

void MenuSetup::setupRosterOptions(Menu* menu, std::vector<std::string> data)
{
	Overlay overlay(menu->getRenderer());

	float xLocation = 66.5f;
	float topRosterPos = 84.1f;
	float rosterGap = 15.8f;

	float optionSize = 1.5f;
	float optionWidth = (9.0f / optionSize) * 2.0f;
	float optionHeight = (16.0f / optionSize);

	float boxBuffer = 1.0f;

	float widthBuffer = (9.0f / boxBuffer);
	float heightBuffer = (16.0f / boxBuffer);

	float boxWidth = optionWidth + widthBuffer;
	float boxHeight = (optionHeight * data.size()) + heightBuffer;

	Button* previous = nullptr;

	for (int i = 0; i < data.size(); i++)
	{
		Button* button = new Button;

		button->text = data.at(i);

		button->data = i;

		button->renderData = ButtonRenderData{ xLocation, topRosterPos - (rosterGap * i), optionWidth, optionHeight, Color::WHITE };

		if (previous != nullptr)
		{
			previous->down = button;
			button->up = previous;
		}

		previous = button;

		overlay.addButton(button);
	}

	menu->add(MenuOverlay::ROSTER_OPTIONS, overlay);
}
