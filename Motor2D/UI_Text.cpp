#include "UI_Text.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "Brofiler\Brofiler.h"

Text::Text(std::string text, int x, int y): UI_Element(x, y, 0, 0),
text(text)
{
	color = { 0,0,0,255 };
	font = App->font->fonts.front();
	createTexture();
}

Text::~Text()
{
	if (texture != nullptr)
	{
		App->tex->UnLoad(texture);
		texture = nullptr;
	}
}

void Text::createTexture()
{
	if (texture != nullptr)
	{
		App->tex->UnLoad(texture);
		texture = nullptr;
	}

	texture = App->font->Print(text.c_str(), &color, font); //Normal texture
	App->tex->GetSize(texture, tex_width, tex_height);
	section.w = tex_width;
	section.h = tex_height;
}

void Text::BlitElement()
{
	if (active)
	{
		BROFILER_CATEGORY("Text Blit", Profiler::Color::Fuchsia);

		if (texture != nullptr)
		{
			iPoint globalPos = getGlobalPosition();

			App->render->Blit(texture, globalPos.x, globalPos.y, NULL);
		}
	}
}