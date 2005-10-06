/* Siconos version 1.0, Copyright INRIA 2005.
 * Siconos is a program dedicated to modeling, simulation and control
 * of non smooth dynamical systems.
 * Siconos is a free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * Siconos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Siconos; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Contact: Vincent ACARY vincent.acary@inrialpes.fr
*/
#include "RelationXML.h"
using namespace std;

RelationXML::RelationXML():
  rootRelationXMLNode(NULL), computeInputNode(NULL), computeOutputNode(NULL)
{}

RelationXML::RelationXML(xmlNode *relationNode):
  rootRelationXMLNode(relationNode), computeInputNode(NULL), computeOutputNode(NULL)
{
  IN("RelationXML::RelationXML(xmlNode*)\n");
  xmlNode *node;
  string type((char*)relationNode->name);
  if ((node = SiconosDOMTreeTools::findNodeChild(this->rootRelationXMLNode, COMPUTE_INPUT_TAG)) != NULL)
    computeInputNode = node;
  else
  {
    if (LAGRANGIAN_NON_LINEAR_RELATION_TAG == type)
      XMLException::selfThrow("RelationXML - RelationXML::RelationXML(xmlNode *relationNode) error : tag " + COMPUTE_INPUT_TAG + " not found.");
  }
  if ((node = SiconosDOMTreeTools::findNodeChild(this->rootRelationXMLNode, COMPUTE_OUTPUT_TAG)) != NULL)
    computeOutputNode = node;
  else
  {
    if (LAGRANGIAN_NON_LINEAR_RELATION_TAG == type)
      XMLException::selfThrow("RelationXML - RelationXML::RelationXML(xmlNode *relationNode) error : tag " + COMPUTE_OUTPUT_TAG + " not found.");
  }
  OUT("RelationXML::RelationXML(xmlNode*)\n");
}

RelationXML::~RelationXML()
{}


void RelationXML::setComputeInputPlugin(const string&  plugin)
{
  if (computeInputNode == NULL)
  {
    computeInputNode = SiconosDOMTreeTools::createSingleNode(rootRelationXMLNode, COMPUTE_INPUT_TAG);
    xmlNewProp(computeInputNode, (xmlChar*)(PLUGIN_ATTRIBUTE.c_str()), (xmlChar*)plugin.c_str());
  }
  else SiconosDOMTreeTools::setStringAttributeValue(computeInputNode, PLUGIN_ATTRIBUTE, plugin);
}

void RelationXML::setComputeOutputPlugin(const string&  plugin)
{
  if (computeOutputNode == NULL)
  {
    computeOutputNode = SiconosDOMTreeTools::createSingleNode(rootRelationXMLNode, COMPUTE_OUTPUT_TAG);
    xmlNewProp(computeOutputNode, (xmlChar*)(PLUGIN_ATTRIBUTE.c_str()), (xmlChar*)plugin.c_str());
  }
  else SiconosDOMTreeTools::setStringAttributeValue(computeOutputNode, PLUGIN_ATTRIBUTE, plugin);
}

void RelationXML::updateRelationXML(xmlNode* node, Relation* rel)
{
  IN("RelationXML::updateRelationXML\n");
  rootRelationXMLNode = node;
  OUT("RelationXML::updateRelationXML\n");
}

string RelationXML::getComputeInputPlugin() const
{
  if (!isComputeInputPlugin())
    XMLException::selfThrow("RelationXML - getComputeInputPlugin : computeInput is not calculated from a plugin");
  return  SiconosDOMTreeTools::getStringAttributeValue(computeInputNode, PLUGIN_ATTRIBUTE);
}
string RelationXML::getComputeOutputPlugin() const
{
  if (!isComputeOutputPlugin())
    XMLException::selfThrow("RelationXML - getComputeOutputPlugin : computeOutput is not calculated from a plugin");
  return  SiconosDOMTreeTools::getStringAttributeValue(computeOutputNode, PLUGIN_ATTRIBUTE);
}
