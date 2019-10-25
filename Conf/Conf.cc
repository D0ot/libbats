#include "conf.ih"

Conf::Conf()
  : d_doc(xmlNewDoc((const xmlChar*)"1.0"))
{
  LIBXML_TEST_VERSION;


  // initializ the pointers
  xpathCtx = nullptr;
  d_doc = nullptr;
}

/**
  *  @param confFile specifies the path to the xml configuration file.
  */
Conf::Conf(std::string const &confFile)
  : Conf()
{
  // initializ the pointers
  xpathCtx = nullptr;
  d_doc = nullptr;

  parseConf(confFile);
}

