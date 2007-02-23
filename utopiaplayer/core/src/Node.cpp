/******************************************************************************\
*  Utopia Player - A cross-platform, multilingual, tagging media manager       *
*  Copyright (C) 2006-2007 John Eric Martin <cpuwhiz105@users.sourceforge.net> *
*                                                                              *
*  This program is free software; you can redistribute it and/or modify        *
*  it under the terms of the GNU General Public License version 2 as           *
*  published by the Free Software Foundation.                                  *
*                                                                              *
*  This program is distributed in the hope that it will be useful,             *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of              *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
*  GNU General Public License for more details.                                *
*                                                                              *
*  You should have received a copy of the GNU General Public License           *
*  along with this program; if not, write to the                               *
*  Free Software Foundation, Inc.,                                             *
*  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                   *
\******************************************************************************/

#include "Node.h"

Node::Node(int input_count, int output_count, int channels) : mChannels(channels)
{
	for(int i = 0; i < input_count; i++)
	{
		mInputNodes << 0;
		mInputPorts << -1;
	}
	for(int i = 0; i < output_count; i++)
	{
		mOutputNodes << 0;
		mOutputPorts << -1;
	}
};

Node::~Node()
{
	// Unglue all inputs and outputs

	for(int i = 0; i < mInputNodes.count(); i++)
	{
		if( !mInputNodes.at(i) )
			continue;

		unglue( this, i, mInputNodes.at(i), mInputPorts.at(i) );
	}

	for(int i = 0; i < mOutputNodes.count(); i++)
	{
		if( !mOutputNodes.at(i) )
			continue;

		unglue( this, i, mOutputNodes.at(i), mOutputPorts.at(i) );
	}
};

void Node::setInput(int port, Node *node, int nodePort)
{
	mInputNodes[port] = node;
	mInputPorts[port] = nodePort;
};

void Node::setOutput(int port, Node *node, int nodePort)
{
	mOutputNodes[port] = node;
	mOutputPorts[port] = nodePort;
};

QList<Node*> Node::inputs() const
{
	return mInputNodes;
};

QList<Node*> Node::outputs() const
{
	return mOutputNodes;
};

Node* Node::input(int port) const
{
	if(port < 0 || port >= mInputPorts.count())
		return 0;

	return mInputNodes.at(port);
};

Node* Node::output(int port) const
{
	if(port < 0 || port >= mOutputPorts.count())
		return 0;

	return mOutputNodes.at(port);
};

int Node::input(float **samples, int count)
{
	for(int i; i < count; i++)
	{
		mBuffer.enqueue(samples[i]);
	}
	return count;
};

int Node::output(float **samples, int count)
{
	int output = count < mBuffer.count() ? count : mBuffer.count();
	for(int i; i < output; i++)
	{
		samples[i] = mBuffer.dequeue();
	}
	return output;
};

int Node::inputCount()
{
	return mInputNodes.count();
};

void Node::reset()
{
	mBuffer.clear();
};

int Node::outputCount()
{
	return mOutputNodes.count();
};

void Node::glue(Node *node1, int node1port, Node *node2, int node2port)
{
	if(!node1 || !node2)
		return;

	if(node1->outputCount() <= node1port || node2->inputCount() <= node2port);
		return;

	node1->setOutput(node1port, node2, node2port);
	node2->setInput(node2port, node1, node1port);
};

void Node::unglue(Node *node1, int node1port, Node *node2, int node2port)
{
	if(!node1 || !node2)
		return;

	if(node1->outputCount() <= node1port || node2->inputCount() <= node2port);
		return;

	node1->setOutput(-1, 0, -1);
	node2->setInput(-1, 0, -1);
};

QMap<QString, QVariant> Node::getOptions() const
{
	return mOptions;
};

QVariant Node::getOption(const QString& optionName) const
{
	if( !mOptions.contains(optionName) )
		return QVariant();

	return mOptions.value(optionName);
};

void Node::setOption(const QString& optionName, const QVariant& option)
{
	mOptions[optionName] = option;
};
