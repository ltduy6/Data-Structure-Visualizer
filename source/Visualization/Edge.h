#pragma once
#include "SceneNode.h"
#include "../Helper/Helper.h"
#include "../Helper/ColorSetting.h"
#include "../ResourceHolder/FontHolder.h"

namespace Visualize {
	class Edge : public SceneNode
	{
	public:
		 int THICKNESS = 5 * Helper::scaleFactorX();
		 int OFFSET = 30;
	public:
		Edge();
		~Edge();
	public:
		virtual void draw();

		void SetSource(Vector2 pos);
		Vector2 GetSource() const;

		void SetDestination(Vector2 pos);
		Vector2 GetDestination() const;

		void SetColor(Color color);
		Color GetColor() const;

		void resetColor(); 
		int getObjectId() const;

		void SetSideOffset(int sideOffset); 
		int GetSideOffset() const; 

		void SetWeight(std::string weight);
		std::string GetWeight() const; 

	private:
		int mSideOffset{ 1 };
		int mThickness{ THICKNESS };
		float textSize{ 36 };
		std::string mWeight{ "" };

		Font font{ FontHolder::getInstance().get(FontID::Roboto) };
		Vector2 mSource{ Vector2 {50, 50} };
		Vector2 mDes{ Vector2 {100, 100} };
		Color mColor{ColorSetting::GetInstance().get(ColorThemeID::EDGE)};
	};
}

