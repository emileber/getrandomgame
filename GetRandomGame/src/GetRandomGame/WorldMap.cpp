/*
 * WorldMap.cpp
 *
 *  Created on: 2012-02-14
 *      Author: Emile
 */

#include "WorldMap.h"
#include <iostream>
#include <fstream>
#include "Graphic/MultiTintedSprite.h"
#include "Graphic/Graphic.h" // accès à Graphic::getInstance(); (pour les dimensions d'écran à jour)

using namespace TileEngine;
// *************OUBLI MOI PAS!

using namespace std;

WorldMap::WorldMap(int size) {

	mapSize = size;
	mScale = 1.0f;
}

WorldMap::~WorldMap() {
	// TODO Auto-generated destructor stub
}

void WorldMap::Scale(float ratio) {
	if (ratio > 0) {
		mScale = ratio;
	}
}

void WorldMap::Update() {
}

void WorldMap::Draw() {
	//c'est sale mais c'est comme ca...
	// Emile dit: Je vais t'arranger ça, prend des notes :P

	// vue que c'est des test, on va pas changer la signature de la function pour rien
	// donc on aura plus besoin de caster comme ça: ((WorldMap*) mWorld)

	// Tu as pas besoin d'un multiTintedSprite ici puisque tu donne la même couleur aux quatres coins.
	// Utilise simplement une sprite et envoi lui une Color3f comme teinte
	// EDIT: j'ai finalement standardisé les fonction Draw de Sprite et MultiTintedSprite et les 2 font
	// la job, j'ai remis MultiTintedSprite pour plus de flexibilité
	Sprite * _grassSprite = new MultiTintedSprite("image/grass.png",
			new SectionRect(0, 0, 40, 40));

	// Plus besoin de passer par 3 float, c'est déjà encapsulé dans Color3f (GraphicType.h)
//	float blue = 0;
//	float red = 0;
//	float green = 0;

	for (int i = 0; i < mapSize; i++) {

		// Évitte de dessiner à l'extérieur de l'écran en bas
		if ((Graphic::getInstance()->GetHeight()
				- i * _grassSprite->Height() * mScale)
				< -_grassSprite->Height()) {
			break;
		}

		// Draw ligne par ligne
		for (int j = 0; j < mapSize; j++) {

			// Évitte de dessiner à l'extérieur de l'écran à droite
			// Break le loop et va à la prochaine ligne.
			if ((j * _grassSprite->Width() * mScale)
					> Graphic::getInstance()->GetWidth()) {
				break;
			}

			// Get la teinte, c'est mieux que d'envoyer des variables
			// les pointeurs se détruisent eux-même en sortant du scope
			Color3f * tint = getTint(j, i);

			_grassSprite->Draw(
					j * _grassSprite->Width() * mScale,
					Graphic::getInstance()->GetHeight()
							- i * _grassSprite->Height() * mScale, mScale, 0,
					tint);
		}

	}
}

Color3f * WorldMap::getTint(int x, int y) {
	Color3f * thatColor;
	switch (biomesMap[x][y]) {

	case 'e':
		thatColor = new Color3f(0.3f, 0, 1);
		break;
	case 'H':
		thatColor = new Color3f(0.6f, 0.8f, 1.0f);
		break;
	case 'A':
		thatColor = new Color3f(0.4f, 0.4f, 0.4f);
		break;
	case 'M':
		thatColor = new Color3f(-1, -1, -1);
		break;
	case 'W':
		thatColor = new Color3f(0, 0.25f, 0);
		break;
	case 'J':
		thatColor = new Color3f(0, 0.5f, 0);
		break;
	case 'R':
		thatColor = new Color3f(0, 0.7f, 0.25f);
		break;
	case 's':
		thatColor = new Color3f(0.5f, 0.9f, 0.4f);
		break;
	case 'S':
		thatColor = new Color3f(0.6f, 0.7f, 0.2f);
		break;
	case 'd':
		thatColor = new Color3f(1.0f, 1.0f, 0.25f);
		break;
	case 'D':
		thatColor = new Color3f(1.0f, 0.75f, 0);
		break;
	case 'G':
		thatColor = new Color3f(0.5f, 0.75f, 0);
		break;
	case 'P':
		thatColor = new Color3f(0.4f, 0.1f, 0.4f);
		break;
	case 'h':
		thatColor = new Color3f(0.6f, 0.3f, 0.6f);
		break;
	case 'F':
		thatColor = new Color3f(0.2f, 0.5f, 0.2f);
		break;
	case 'B':
		thatColor = new Color3f(0.5f, 0.8f, 0.5f);
		break;
	case 'C':
		thatColor = new Color3f(0.2f, 0.5f, 0.4f);
		break;
	case 'b':
		thatColor = new Color3f(0.1f, 1.0f, 0.5f);
		break;
	case 'Z':
		thatColor = new Color3f(0, 1, 0.8f);
		break;
	case 'I':
		thatColor = new Color3f(0.7f, 1, 1);
		break;
	case 'Y':
		thatColor = new Color3f(0.25f, 0, 0.25f);
		break;
	case 'U':
		thatColor = new Color3f(0, 0, 0.2f);
		break;
	case 'k':
		thatColor = new Color3f(0.7f, 0.5f, 0.2f);
		break;
	default:
		thatColor = new Color3f(0, 0, 0);
		break;
	}
	return thatColor;

}

void WorldMap::DropXML() {

//donne un fichier XML lisible avec excel
	ofstream xmldump;
	xmldump.open("map.xml");

	xmldump
			<< "<?xml version=\"1.0\"?>\n<?mso-application progid=\"Excel.Sheet\"?>\n<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\"\nxmlns:o=\"urn:schemas-microsoft-com:office:office\"\nxmlns:x=\"urn:schemas-microsoft-com:office:excel\"\nxmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\"\nxmlns:html=\"http://www.w3.org/TR/REC-html40\">\n<ExcelWorkbook xmlns=\"urn:schemas-microsoft-com:office:excel\">\n <WindowHeight>9525</WindowHeight>\n<WindowWidth>15315</WindowWidth>\n<WindowTopX>360</WindowTopX>\n<WindowTopY>75</WindowTopY>\n <ProtectStructure>False</ProtectStructure>\n <ProtectWindows>False</ProtectWindows>\n </ExcelWorkbook>\n <Styles>\n <Style ss:ID=\"Default\" ss:Name=\"Normal\">\n <Alignment ss:Vertical=\"Bottom\"/>\n<Borders/>\n<Font/>\n<Interior/>\n <NumberFormat/>\n<Protection/>\n </Style>";
	xmldump
			<< "<Style ss:ID=\"H\">\n<Interior ss:Color=\"#F0F0F0\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"A\">\n<Interior ss:Color=\"#686868\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"e\">\n<Interior ss:Color=\"#0000ff\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"M\">\n<Interior ss:Color=\"#333333\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"W\">\n<Interior ss:Color=\"#003300\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"J\">\n<Interior ss:Color=\"#008000\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"R\">\n<Interior ss:Color=\"#00ff48\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"s\">\n<Interior ss:Color=\"#99CC00\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"G\">\n<Interior ss:Color=\"#00ff00\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"S\">\n<Interior ss:Color=\"#99CC00\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"d\">\n<Interior ss:Color=\"#FFFF99\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"D\">\n<Interior ss:Color=\"#FF9900\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"P\">\n<Interior ss:Color=\"#666699\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"h\">\n<Interior ss:Color=\"#800080\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"F\">\n<Interior ss:Color=\"#00B261\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"B\">\n<Interior ss:Color=\"#00ff00\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"C\">\n<Interior ss:Color=\"#008080\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"b\">\n<Interior ss:Color=\"#808000\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"Z\">\n<Interior ss:Color=\"#33CCCC\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"I\">\n<Interior ss:Color=\"#CCFFCC\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"E\">\n<Interior ss:Color=\"#E7fdfd\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"Q\">\n<Interior ss:Color=\"#CCCCFF\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"k\">\n<Interior ss:Color=\"#CCCCFF\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"U\">\n<Interior ss:Color=\"#000055\" ss:Pattern=\"Solid\"/>\n</Style>\n";
	xmldump
			<< "<Style ss:ID=\"Y\">\n<Interior ss:Color=\"#800000\" ss:Pattern=\"Solid\"/>\n</Style>\n";

	int maps = mapSize - 1;
	xmldump
			<< "</Styles>\n<Worksheet ss:Name=\"Sheet1\">\n<Table ss:ExpandedColumnCount=\""
			<< mapSize
			<< "\" ss:ExpandedRowCount=\""
			<< mapSize
			<< "\" x:FullColumns=\"1\"\nx:FullRows=\"1\">\n<Column ss:AutoFitWidth=\"0\" ss:Width=\"19.5\" ss:Span=\""
			<< maps << "\"/>\n";

	for (int i = 0; i < mapSize; i++) {
		xmldump << "<Row>\n";
		for (int j = 0; j < mapSize; j++) {
			xmldump << " <Cell  ss:StyleID=\"" << biomesMap[j][i]
					<< "\"><Data ss:Type=\"String\">" << biomesMap[j][i]
					<< "</Data></Cell>\n";
		}
		xmldump << "</Row>\n";
	}

	xmldump
			<< "  </Table>\n<WorksheetOptions xmlns=\"urn:schemas-microsoft-com:office:excel\">\n<Selected/>\n<Panes>\n<Pane>\n <Number>1</Number>\n <ActiveCol>1</ActiveCol>\n </Pane>\n </Panes>\n <ProtectObjects>False</ProtectObjects>\n <ProtectScenarios>False</ProtectScenarios>\n</WorksheetOptions>\n</Worksheet>\n</Workbook>";

	xmldump.close();
}

