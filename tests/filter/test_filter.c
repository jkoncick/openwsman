#include <stdio.h>
#include "wsman-filter.h"
#include "wsman-names.h"
#include "wsman-xml.h"

static void serialize_filter(void)
{
	hash_t *selectors = hash_create(HASHCOUNT_T_MAX, 0, 0);
	selector_entry *entry1 = NULL;
	entry1 = u_malloc(sizeof(selector_entry)*5);
	entry1[0].type = 0;
	entry1[0].entry.text = "OperatingSystemFilter0";
	entry1[1].type = 0;
        entry1[1].entry.text = "localhost.localdomain";
	entry1[2].type = 0;
        entry1[2].entry.text = "CIM_IndicationFilter";
	entry1[3].type = 0;
        entry1[3].entry.text = "CIM_ComputerSystem";
	entry1[4].type = 0;
	entry1[4].entry.text = "root/interop";
	hash_alloc_insert(selectors, "Name", &entry1[0]);
	hash_alloc_insert(selectors, "SystemName", &entry1[1]);
	hash_alloc_insert(selectors, "CreationClassName", &entry1[2]);
	hash_alloc_insert(selectors, "SystemCreationClassName", &entry1[3]);
	hash_alloc_insert(selectors, "__cimnamespace", &entry1[4]);
	epr_t *epr = epr_create("http://schema.omc-project.org/wbem/wscim/1/cim-schema/2/CIM_IndicationFilter",selectors,NULL);
	filter_t *filter = filter_create(WSM_ASSOCIATION_FILTER_DIALECT, NULL, epr, 0, "CIM_IndicationSubscription", NULL, NULL, NULL, NULL, 0);
	WsXmlDocH doc = ws_xml_create_envelope();
	WsXmlNodeH body = ws_xml_get_soap_body(doc);
	WsXmlNodeH node = ws_xml_add_child(body, XML_NS_ENUMERATION, WSENUM_ENUMERATE, NULL);

	filter_t *filter_cpy = filter_copy(filter); //test filter_copy

	int r = filter_serialize(node, filter_cpy);
	if(r) {
		printf("\t\033[22;31mfilter serialize failed!\033[m\n");
		return;
	}
	ws_xml_dump_doc(stdout, doc);
	ws_xml_destroy_doc(doc);
	hash_free(selectors);
	u_free(entry1);
	epr_destroy(epr);
	filter_destroy(filter);
	filter_destroy(filter_cpy);
	printf("\t\t\033[22;32mfilter serialize successfully!\033[m\n");
}

static void deserialize_filter(void)
{
	WsXmlDocH doc = ws_xml_read_file("./sample.xml", "UTF-8", 0);
	WsXmlNodeH node = ws_xml_get_soap_body(doc);
	node = ws_xml_get_child(node, 0, XML_NS_ENUMERATION, WSENUM_ENUMERATE);
	filter_t *filter = filter_deserialize(node);
	if(filter == NULL) {
		printf("\t\t\033[22;31mfilter deserialize failed!\033[m\n");
		return;
	}
	ws_xml_destroy_doc(doc);
	doc = ws_xml_create_envelope();
        WsXmlNodeH body = ws_xml_get_soap_body(doc);
        node = ws_xml_add_child(body, XML_NS_ENUMERATION, WSENUM_ENUMERATE, NULL);
	int r = filter_serialize(node, filter);
        if(r) {
                printf("\t\t\033[22;31mfilter serialize failed!\033[m\n");
                return;
        }
        ws_xml_dump_doc(stdout, doc);
        ws_xml_destroy_doc(doc);
	filter_destroy(filter);
	printf("\t\t\033[22;32mfilter deserialize successfully!\033[m\n");
}

int main(void)
{
	serialize_filter();
	deserialize_filter();
	return 0;
}
