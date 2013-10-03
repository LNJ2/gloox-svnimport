/*
  Copyright (c) 2008-2013 by Jakob Schroeter <js@camaya.net>
  This file is part of the gloox library. http://camaya.net/gloox

  This software is distributed under a license. The full license
  agreement can be found in the file LICENSE in this distribution.
  This software may not be copied, modified, sold or distributed
  other than expressed in the named license agreement.

  This software is distributed without any warranty.
*/


#include "jinglepluginfactory.h"
#include "tag.h"
#include "jingleplugin.h"
#include "util.h"

namespace gloox
{

  namespace Jingle
  {

    PluginFactory::PluginFactory()
    {
    }

    PluginFactory::~PluginFactory()
    {
      util::clearList( m_plugins );
    }

    void PluginFactory::registerPlugin( Plugin* plugin )
    {
      if( plugin )
        m_plugins.push_back( plugin );
    }

    void PluginFactory::addPlugins( Plugin& plugin, const Tag* tag )
    {
      if( !tag )
        return;

      ConstTagList::const_iterator it;
      
      PluginList::const_iterator itp = m_plugins.begin();
      for( ; itp != m_plugins.end(); ++itp )
      {
        const ConstTagList& match = tag->findTagList( (*itp)->filterString() );
        it = match.begin();
        for( ; it != match.end(); ++it )
        {
          Plugin* pl = (*itp)->newInstance( (*it) );
          if( pl )
          {
            plugin.addPlugin( pl );
          }
        }
      }
    }

  }

}
