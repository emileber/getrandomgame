/*
 * WorldMap.cpp
 *
 *  Created on: 2012-02-14
 *      Author: Emile
 */

#include "WorldMap.h"
#include <iostream>
#include <fstream>

using namespace std;

WorldMap::WorldMap(int size) {

	mapSize = size;
}

WorldMap::~WorldMap() {
	// TODO Auto-generated destructor stub
}

void WorldMap::Update() {
}

void WorldMap::Draw() {

	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			cout << biomesMap[j][i] << '\t';
		}
		cout << endl;
	}
	cout << "Height map" << endl;
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			cout << hMap[j][i] << '\t';
		}
		cout << endl;
	}
	cout << "Humidity map" << endl;
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			cout << huMap[j][i] << '\t';
		}
		cout << endl;
	}
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
