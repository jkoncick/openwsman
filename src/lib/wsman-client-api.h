/*******************************************************************************
 * Copyright (C) 2004-2006 Intel Corp. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  - Neither the name of Intel Corp. nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL Intel Corp. OR THE CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************/

/**
 * @author Anas Nashif
 */

#ifndef WSMANCLIENT_API_H_
#define WSMANCLIENT_API_H_


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "u/libu.h"
#include "wsman-xml-api.h"
#include "wsman-namespaces.h"



#define FLAG_NONE                            0
#define FLAG_ENUMERATION_COUNT_ESTIMATION    1
#define FLAG_ENUMERATION_OPTIMIZATION        2
#define FLAG_ENUMERATION_ENUM_EPR            4
#define FLAG_ENUMERATION_ENUM_OBJ_AND_EPR    8
#define FLAG_DUMP_REQUEST                    16
#define FLAG_IncludeSubClassProperties       32
#define FLAG_ExcludeSubClassProperties       64
#define FLAG_POLYMORPHISM_NONE               128



#define PROCESSED_MSG_ID_MAX_SIZE            200
#define WSMAN_MINIMAL_ENVELOPE_SIZE_REQUEST  8192

#define DMTF_WSMAN_SPEC_1

#define SOAP1_2_CONTENT_TYPE       "application/soap+xml; charset=utf-8"
#define SOAP_CONTENT_TYPE          "application/soap+xml"

#define SOAP_SKIP_DEF_FILTERS       0x01
#define SOAP_ACTION_PREFIX          0x02 // otherwise exact
#define SOAP_ONE_WAY_OP             0x04
#define SOAP_NO_RESP_OP             0x08
#define SOAP_DONT_KEEP_INDOC        0x10

#define SOAP_CLIENT_RESPONSE        0x20 // internal use
#define SOAP_CUSTOM_DISPATCHER      0x40 // internal use
#define SOAP_IDENTIFY_DISPATCH      0x80 // internal use


#define WSMID_IDENTIFY              "Identify"
#define WSMID_IDENTIFY_RESPONSE     "IdentifyResponse"
#define WSMID_PROTOCOL_VERSION      "ProtocolVersion"
#define WSMID_PRODUCT_VENDOR        "ProductVendor"
#define WSMID_PRODUCT_VERSION       "ProductVersion"


#define XML_SCHEMA_NIL          "nil"


#define WSA_TO_ANONYMOUS                                             \
  "http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous"
#define WSA_MESSAGE_ID              "MessageID"
#define WSA_ADDRESS         "Address"
#define WSA_EPR             "EndpointReference"
#define WSA_ACTION          "Action"
#define WSA_RELATES_TO              "RelatesTo"
#define WSA_TO              "To"
#define WSA_REPLY_TO                "ReplyTo"
#define WSA_FROM                "From"
#define WSA_FAULT_TO            "FaultTo"
#define WSA_REFERENCE_PROPERTIES    "ReferenceProperties"
#define WSA_REFERENCE_PARAMETERS    "ReferenceParameters"
#define WSA_ACTION_FAULT                                    \
  "http://schemas.xmlsoap.org/ws/2004/08/addressing/fault"



#define SOAP_ENVELOPE           "Envelope"
#define SOAP_HEADER         "Header"
#define SOAP_BODY           "Body"
#define SOAP_FAULT          "Fault"
#define SOAP_CODE           "Code"
#define SOAP_VALUE          "Value"
#define SOAP_SUBCODE            "Subcode"
#define SOAP_REASON         "Reason"
#define SOAP_TEXT           "Text"
#define SOAP_LANG           "lang"
#define SOAP_DETAIL         "Detail"
#define SOAP_FAULT_DETAIL       "FaultDetail"
#define SOAP_MUST_UNDERSTAND        "mustUnderstand"
#define SOAP_VERSION_MISMATCH           "VersionMismatch"
#define SOAP_UPGRADE            "Upgrade"
#define SOAP_SUPPORTED_ENVELOPE         "SupportedEnvelope"


#define TRANSFER_ACTION_PUT     "http://schemas.xmlsoap.org/ws/2004/09/transfer/Put"
#define TRANSFER_ACTION_GET     "http://schemas.xmlsoap.org/ws/2004/09/transfer/Get"
#define TRANSFER_GET            "Get"
#define TRANSFER_PUT            "Put"
#define TRANSFER_CREATE         "Create"

#define ENUM_ACTION_ENUMERATE   "http://schemas.xmlsoap.org/ws/2004/09/enumeration/Enumerate"
#define ENUM_ACTION_RELEASE     "http://schemas.xmlsoap.org/ws/2004/09/enumeration/Release"
#define ENUM_ACTION_PULL        "http://schemas.xmlsoap.org/ws/2004/09/enumeration/Pull"
#define WSENUM_ENUMERATE        "Enumerate"
#define WSENUM_ENUMERATE_RESP           "EnumerateResponse"
#define WSENUM_PULL             "Pull"
#define WSENUM_PULL_RESP        "PullResponse"
#define WSENUM_END_TO           "EndTo"
#define WSENUM_EXPIRES          "Expires"
#define WSENUM_FILTER           "Filter"
#define WSENUM_DIALECT          "Dialect"
#define WSENUM_ENUMERATION_CONTEXT  "EnumerationContext"
#define WSENUM_MAX_TIME         "MaxTime"
#define WSENUM_MAX_ELEMENTS     "MaxElements"
#define WSENUM_MAX_CHARACTERS           "MaxCharacters"
#define WSENUM_ITEMS            "Items"
#define WSENUM_END_OF_SEQUENCE          "EndOfSequence"
#define WSENUM_RELEASE          "Release"
#define WSENUM_RELEASE_RESP     "ReleaseResponse"
#define WSENUM_RENEW            "Renew"
#define WSENUM_RENEW_RESP       "RenewResponse"
#define WSENUM_GET_STATUS       "GetStatus"
#define WSENUM_GET_STATUS_RESP          "GetStatusResponse"
#define WSENUM_ENUMERATION_END          "EnumerationEnd"
#define WSENUM_REASON           "Reason"
#define WSENUM_CODE         "Code"
#define WSENUM_SOURCE_SHUTTING_DOWN "SourceShuttingDown"
#define WSENUM_SOURCE_CANCELING         "SourceCanceling"
#define WSENUM_ACTION_FAULT "http://schemas.xmlsoap.org/ws/2004/09/enumeration/fault"


#define WSM_SYSTEM          "System"
#define WSM_RESOURCE_URI        "ResourceURI"
#define WSM_SELECTOR_SET        "SelectorSet"
#define WSM_SELECTOR            "Selector"
#define WSM_NAME                "Name"
#define WSM_REQUEST_TOTAL       "RequestTotalItemsCountEstimate"
#define WSM_TOTAL_ESTIMATE              "TotalItemsCountEstimate"
#define WSM_OPTIMIZE_ENUM               "OptimizeEnumeration"
#define WSM_MAX_ELEMENTS                "MaxElements"
#define WSM_ENUM_EPR                    "EnumerateEPR"
#define WSM_ENUM_OBJ_AND_EPR            "EnumerateObjectAndEPR"
#define WSM_ENUM_MODE                   "EnumerationMode"
#define WSM_ITEM                        "Item"
#define WSM_FRAGMENT_TRANSFER           "FragmentTransfer"
#define WSM_XML_FRAGMENT                "XmlFragment"

#define WSM_MAX_ENVELOPE_SIZE           "MaxEnvelopeSize"
#define WSM_OPERATION_TIMEOUT           "OperationTimeout"
#define WSM_FAULT_SUBCODE           "FaultSubCode"
#define WSMAN_ACTION_FAULT            "http://schemas.dmtf.org/wbem/wsman/1/wsman/fault"


#define WSXF_ACTION_FAULT            "http://schemas.xmlsoap.org/ws/2004/09/transfer/fault"


// WSMB - Binding
#define WSMB_POLYMORPHISM_MODE          "PolymorphismMode"
#define WSMB_INCLUDE_SUBCLASS_PROP      "IncludeSubClassProperties"
#define WSMB_EXCLUDE_SUBCLASS_PROP      "ExcludeSubClassProperties"
#define WSMB_NONE      "None"


// Catalog

#define WSMANCAT_RESOURCE       "Resource"
#define WSMANCAT_RESOURCE_URI           "ResourceUri"
#define WSMANCAT_VERSION        "Version"
#define WSMANCAT_NOTES          "Notes"
#define WSMANCAT_VENDOR         "Vendor"
#define WSMANCAT_DISPLAY_NAME           "DisplayName"
#define WSMANCAT_KEYWORDS       "Keywords"
#define WSMANCAT_ACCESS         "Access"
#define WSMANCAT_RELATIONSHIPS          "Relationsships"
#define WSMANCAT_COMPLIANCE     "Compliance"
#define WSMANCAT_OPERATION      "Operation"
#define WSMANCAT_SELECTOR_SET           "SelectorSet"
#define WSMANCAT_SELECTOR       "Selector"
#define WSMANCAT_OPTION_SET     "OptionSet"
#define WSMANCAT_ACTION         "Action"
#define WSMANCAT_SELECTOR_SET_REF       "SelectorSetRef"
#define WSMANCAT_LOCATION       "Location"
#define WSMANCAT_NAME           "Name"
#define WSMANCAT_TYPE           "Type"


// Filter Dialects
#define WSM_SELECTOR_FILTER_DIALECT     "http://schemas.dmtf.org/wbem/wsman/1/wsman/SelectorFilter"
#define WSM_WQL_FILTER_DIALECT          "http://schemas.microsoft.com/wbem/wsman/1/WQL"
#define WSM_XPATH_FILTER_DIALECT        "http://www.w3.org/TR/1999/REC-xpath-19991116"


#define WSFW_RESPONSE_STR       "Response"
#define WSFW_INDOC          "indoc"

#define WSFW_ENUM_PREFIX        "_en."


// context

#define WS_CONTEXT_TYPE_MASK        0x0f
#define WS_CONTEXT_FREE_DATA        0x80

#define WS_CONTEXT_TYPE_STRING      0x01
#define WS_CONTEXT_TYPE_ULONG       0x02
#define WS_CONTEXT_TYPE_XMLDOC      0x03
#define WS_CONTEXT_TYPE_XMLNODE     0x04
#define WS_CONTEXT_TYPE_BLOB        0x05
#define WS_CONTEXT_TYPE_FAULT       0x06


#define CIM_NAMESPACE_SELECTOR          "__cimnamespace"



  struct _WsManClient;
  typedef struct _WsManClient WsManClient;


  typedef struct _WsManClientStatus {
    unsigned int rc;
    char *msg;
  } WsManClientStatus;


  typedef struct __clientData {
    char *hostName;
    unsigned int port;
    char *user;
    char *pwd;
    char *scheme;
    char *endpoint;
    unsigned int auth_method;
    int  status;
  } WsManClientData;


  typedef struct __credentialData {
    char * certFile;
    char * keyFile;
    unsigned int verify_peer;
  } WsManCredentialData;

  typedef struct proxyData {
    char * proxy;
    char * proxy_auth;
  } WsManProxyData;

  enum __WsmanAction 
    {
      WSMAN_ACTION_NONE = 0, 
      WSMAN_ACTION_TRANSFER_GET,
      WSMAN_ACTION_TRANSFER_PUT,
      WSMAN_ACTION_ENUMERATION,
      WSMAN_ACTION_PULL, 
      WSMAN_ACTION_RELEASE,
      WSMAN_ACTION_CUSTOM,    
      WSMAN_ACTION_TRANSFER_CREATE,    
      WSMAN_ACTION_IDENTIFY,
      WSMAN_ACTION_TEST
    };
  typedef enum __WsmanAction WsmanAction;

  struct _actionOptions {
    unsigned char       flags;
    char *              filter;
    char *              dialect;
    char *              fragment;
    char *              cim_ns;
    hash_t				*selectors;
    hash_t              *properties;
    unsigned int        timeout;
    unsigned int        max_envelope_size;
    unsigned int        max_elements;
   
  };
  typedef struct _actionOptions actionOptions;

  struct _WsManConnection {
    u_buf_t*	request;
    u_buf_t*	response;
  };
  typedef struct _WsManConnection WsManConnection;

  struct _WsManClient {
    void*               hdl;
    WsContextH          wscntx;
    WsManClientData     data;
    WsManConnection     *connection;
    long                response_code;
    void                *transport;
  };



  WsManClient*
  wsman_create_client( const char *hostname,
                 const int port,
                 const char *path,
                 const char *scheme,
                 const char *username,
                 const char *password);



            /* Wsman actions handling */
  WsXmlDocH wsman_build_envelope(WsContextH cntx, char* action,
                                 char* reply_to_uri, char* resource_uri,
                                 char* to_uri, actionOptions options);
  WsXmlDocH wsman_identify(WsManClient *cl, actionOptions options);
  WsXmlDocH ws_transfer_get(WsManClient *cl, char *resourceUri,
                            actionOptions options); 
  WsXmlDocH ws_transfer_put(WsManClient *cl, char *resourceUri,
                            actionOptions options);
  WsXmlDocH ws_transfer_create(WsManClient *cl, char *resourceUri,
                               actionOptions options);
  WsXmlDocH wsenum_enumerate(WsManClient *cl, char *resourceUri,
                             actionOptions options);
  WsXmlDocH wsenum_pull(WsManClient *cl, char *resourceUri, 
                        char *enumContext , actionOptions options);
  WsXmlDocH wsenum_release(WsManClient *cl, char *resourceUri,
                           char *enumContext , actionOptions options);
  WsXmlDocH wsman_invoke(WsManClient *cl, char *resourceUri,char *method,
                         actionOptions options);



  void wsman_send_request(WsManClient *cl, WsXmlDocH request);
  WsXmlDocH wsman_build_envelope_from_response(WsManClient *cl);




  WsXmlDocH 
  wsman_create_request( WsManClient *cl,
                        WsmanAction action,
                        char *method,
                        char *resource_uri,
                        actionOptions options,
                        void *data);

  char *wsenum_get_enum_context(WsXmlDocH doc);
  void wsman_add_fragment_transfer( WsXmlDocH doc, char *fragment);
  void wsman_add_namespace_as_selector( WsXmlDocH doc, char *_namespace);
  void  wsman_add_selector_from_uri(WsXmlDocH doc, char *resourceUri);



            /* Action options handling */
  void initialize_action_options(actionOptions *op);
  void destroy_action_options(actionOptions *op);
  void wsman_add_selectors_from_query_string(actionOptions *options,
                                             const char *query_string);
  void wsman_add_selector_from_options( WsXmlDocH doc,  actionOptions options);
  void wsman_set_action_option(actionOptions *options, unsigned int);
  void wsman_set_options_from_uri( char *resourceUri, actionOptions *options);


            /* Misc */
  char* wsman_make_action(char* uri, char* opName);
  void wsman_remove_query_string(char * resourceUri, char **result);
  hash_t *wsman_create_hash_from_query_string(const char *query_string);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*WSMANCLIENT_H_*/
