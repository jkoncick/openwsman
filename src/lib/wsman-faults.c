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
#ifdef HAVE_CONFIG_H
#include <wsman_config.h>
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include <u/libu.h>
#include "wsman-xml-api.h"
#include "wsman-client-api.h"
#include "wsman-soap.h"
#include "wsman-dispatcher.h"

#include "wsman-xml.h"
#include "wsman-xml-serializer.h"
#include "wsman-soap-envelope.h"
#include "wsman-soap-message.h"
#include "wsman-faults.h"


#define FAULT_XPATH_EXPR  "/s:Envelope/s:Body/s:Fault/s:Code/s:Value"

WsmanFaultDetailTable fault_detail_table[] =
{
	{ WSMAN_DETAIL_OK, NULL },
	{ WSMAN_DETAIL_ACK, "Ack" },
	{ WSMAN_DETAIL_ACTION_MISMATCH, "ActionMismatch" },
	{ WSMAN_DETAIL_ALREADY_EXISTS, "AlreadyExists" },
	{ WSMAN_DETAIL_AMBIGUOUS_SELECTORS, "AmbigousSelectors" },
	{ WSMAN_DETAIL_ASYNCHRONOUS_REQUEST, "AsynchronousRequest" },
	{ WSMAN_DETAIL_ADDRESSING_MODE, "AddressingMode" },
	{ WSMAN_DETAIL_AUTHERIZATION_MODE, "AutherizationMode" },
	{ WSMAN_DETAIL_BOOKMARKS, "Bookmarks" },
	{ WSMAN_DETAIL_CHARECHTER_SET, "CharechterSet" },
	{ WSMAN_DETAIL_DELIVERY_RETRIES, "DeliveryRetries" },
	{ WSMAN_DETAIL_DUPLICATE_SELECTORS, "DuplicateSelectors" },
	{ WSMAN_DETAIL_ENCODING_TYPE, "EncodingType" },
	{ WSMAN_DETAIL_ENUMERATION_MODE, "EnumerationMode" },
	{ WSMAN_DETAIL_EXPIRATION_TIME, "ExpirationTime" },
	{ WSMAN_DETAIL_EXPIRED, "Expired" },
	{ WSMAN_DETAIL_FILTERING_REQUIRED, "FilteringRequired" },
	{ WSMAN_DETAIL_FORMAT_MISMATCH, "FormatMismatch" },
	{ WSMAN_DETAIL_FORMAT_SECURITY_TOKEN, "FormatSecurityTocken" },
	{ WSMAN_DETAIL_FRAGMENT_LEVEL_ACCESS, "FragmentLevelAccess" },
	{ WSMAN_DETAIL_HEARTBEATS, "Heartbeats" },
	{ WSMAN_DETAIL_INSECURE_ADDRESS, "InsecureAddress" },
	{ WSMAN_DETAIL_INSUFFICIENT_SELECTORS, "InsufficientSelectors" },
	{ WSMAN_DETAIL_INVALID, "Invalid" },
	{ WSMAN_DETAIL_INVALID_ADDRESS, "InvalidAddress" },
	{ WSMAN_DETAIL_INVALID_FORMAT, "InvalidFormat" },
	{ WSMAN_DETAIL_INVALID_FRAGMENT, "InvalidFragment" },
	{ WSMAN_DETAIL_INVALID_NAME, "InvalidName" },
	{ WSMAN_DETAIL_INVALID_NAMESPACE, "InvalidNamespace" },
	{ WSMAN_DETAIL_INVALID_RESOURCEURI, "InvalidResourceURI" },
	{ WSMAN_DETAIL_INVALID_SELECTOR_ASSIGNMENT, "InvalidSelectorAssignment" },
	{ WSMAN_DETAIL_INVALID_SYSTEM, "InvalidSystem" },
	{ WSMAN_DETAIL_INVALID_TIMEOUT, "InvalidTimeout" },
	{ WSMAN_DETAIL_INVALID_VALUE, "InvalidValue" },
	{ WSMAN_DETAIL_INVALID_VALUES, "InvalidValues" },
	{ WSMAN_DETAIL_LOCALE, "Locale" },
	{ WSMAN_DETAIL_MAX_ELEMENTS, "MaxElements" },
	{ WSMAN_DETAIL_MAX_ENVELOPE_POLICY, "MaxEnvelopePolicy" },
	{ WSMAN_DETAIL_MAX_ENVELOPE_SIZE, "MaxEnvelopeSize" },
	{ WSMAN_DETAIL_MAX_TIME, "MaxTime" },
	{ WSMAN_DETAIL_MINIMUM_ENVELOPE_LIMIT, "MinimumEnvelopeLimit" },
	{ WSMAN_DETAIL_MISSING_VALUES, "MissingValues" },
	{ WSMAN_DETAIL_NOT_SUPPORTED, "NotSupported" },
	{ WSMAN_DETAIL_OPERATION_TIMEOUT, "OperationTimeout" },
	{ WSMAN_DETAIL_OPTION_LIMIT, "OptionLimit" },
	{ WSMAN_DETAIL_OPTION_SET, "OptionSet" },
	{ WSMAN_DETAIL_READ_ONLY, "ReadOnly" },
	{ WSMAN_DETAIL_RESOURCE_OFFLINE, "ResourceOffline" },
	{ WSMAN_DETAIL_RENAME, "Rename" },
	{ WSMAN_DETAIL_SELECTOR_LIMIT, "SelectorLimit" },
	{ WSMAN_DETAIL_SERVICE_ENVELOPE_LIMIT, "ServiceEnvelopeLimit" },
	{ WSMAN_DETAIL_TARGET_ALREADY_EXISTS, "TargetAlreadyExists" },
	{ WSMAN_DETAIL_TYPE_MISMATCH, "TypeMismatch" },
	{ WSMAN_DETAIL_UNEXPECTED_SELECTORS, "UnexpectedSelectors" },
	{ WSMAN_DETAIL_UNREPORTABLE_SUCCESS, "UnreportableSuccess" },
	{ WSMAN_DETAIL_UNUSABLE_ADDRESS, "UnusableAddress" },
	{ WSMAN_DETAIL_URI_LIMIT_EXCEEDED, "UriLimitExceeded" },
	{ WSMAN_DETAIL_WHITESPACE, "Whitespace" },

	// WS-Addressing
	{ WSA_DETAIL_DUPLICATE_MESSAGE_ID, "DuplicateMessageID" },

	// SOAP
	{ SOAP_DETAIL_HEADER_NOT_UNDERSTOOD, "HeaderNotUnderstood" },

	// OpenWSMAN
	{ OWSMAN_DETAIL_ENDPOINT_ERROR, "Unknown" },
	{ OWSMAN_NO_DETAILS, "Unknown" }
};



WsmanFaultCodeTable fault_code_table[] =
{
	{
		SOAP_FAULT_MUSTUNDERSTAND,
		WSA_ACTION_FAULT,
		XML_NS_SOAP_1_2,
		FAULT_MUSTUNDERSTAND_CODE,
		"",
		"The WS-Management service cannot process a SOAP header in the request that" \
		"is marked as mustUnderstand by the client.  This could be caused by the use" \
		"of a version of the protocol which is not supported, or may be an" \
		"incompatibility  between the client and server implementations."
	},
	{
		WSA_ENDPOINT_UNAVAILABLE,
		WSA_ACTION_FAULT,
		XML_NS_ADDRESSING,
		FAULT_SENDER_CODE,
		"EndpointUnavailable",
		""
	},
	{
		WSMAN_ACCESS_DENIED,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_SENDER_CODE,
		"AccessDenied",
		"The sender was not authorized to access the resource."
	},
	{
		WSA_ACTION_NOT_SUPPORTED,
		WSA_ACTION_FAULT,
		XML_NS_ADDRESSING,
		FAULT_SENDER_CODE,
		"ActionNotSupported",
		"The action is not supported by the service."
	},
	{
		WSMAN_ALREADY_EXISTS,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_SENDER_CODE,
		"AlreadyExists",
		"The sender attempted to create a resource which already exists."
	},
	{
		WSEN_CANNOT_PROCESS_FILTER,
		WSENUM_ACTION_FAULT,
		XML_NS_ENUMERATION,
		FAULT_SENDER_CODE,
		"CannotProcessFilter",
		"The requested filter could not be processed."
	},
	{
		WSMAN_CANNOT_PROCESS_FILTER,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_SENDER_CODE,
		"CannotProcessFilter",
		"The requested filter could not be processed."
	},
	{
		WSMAN_CONCURRENCY,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_SENDER_CODE,
		"Concurrency",
		"The action could not be completed due to concurrency or locking problems."
	},
	{
		WSMAN_CONCURRENCY,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_SENDER_CODE,
		"Concurrency",
		"The action could not be completed due to concurrency or locking problems."
	},
	{
		WSA_DESTINATION_UNREACHABLE,
		WSA_ACTION_FAULT,
		XML_NS_ADDRESSING,
		FAULT_SENDER_CODE,
		"DestinationUnreachable",
		"No route can be determined to reach the destination role defined by the WS-Addressing To."
	},
	{
		WSMAN_ENCODING_LIMIT,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_SENDER_CODE,
		"EncodingLimit",
		"An internal encoding limit was exceeded in a request or would be violated if the message were processed."
	},
	{
		WSA_ENDPOINT_UNAVAILABLE,
		WSA_ACTION_FAULT,
		XML_NS_ADDRESSING,
		FAULT_RECEIVER_CODE,
		"EndpointUnavailable",
		"The specified endpoint is currently unavailable."
	},
	{
		WSEN_FILTER_DIALECT_REQUESTED_UNAVAILABLE,
		WSENUM_ACTION_FAULT,
		XML_NS_ENUMERATION,
		FAULT_SENDER_CODE,
		"FilterDialectRequestedUnavailable",
		"The requested filtering dialect is not supported."
	},
	{
		WSEN_FILTERING_NOT_SUPPORTED,
		WSENUM_ACTION_FAULT,
		XML_NS_ENUMERATION,
		FAULT_SENDER_CODE,
		"FilteringNotSupported",
		"Filtered enumeration is not supported."
	},
	{
		WSMAN_FRAGMENT_DIALECT_NOT_SUPPORTED,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_RECEIVER_CODE,
		"FragmentDialectNotSupported",
		"The requested fragment filtering dialect or language is not supported."
	},
	{
		WSMAN_INTERNAL_ERROR,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_RECEIVER_CODE,
		"InternalError",
		"The service cannot comply with the request due to internal processing errors."
	},
	{
		WSEN_INVALID_ENUMERATION_CONTEXT,
		WSENUM_ACTION_FAULT,
		XML_NS_ENUMERATION,
		FAULT_RECEIVER_CODE,
		"InvalidEnumerationContext",
		"The supplied enumeration context is invalid."
	},
	{
		WSA_INVALID_MESSAGE_INFORMATION_HEADER,
		WSA_ACTION_FAULT,
		XML_NS_ADDRESSING,
		FAULT_SENDER_CODE,
		"InvalidMessageInformationHeader",
		"A message information header is not valid and the message cannot be processed."
	},
	{
		WSMAN_INVALID_OPTIONS,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_SENDER_CODE,
		"InvalidOptions",
		"One or more options are not valid."
	},
	{
		WSMAN_INVALID_PARAMETER,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_SENDER_CODE,
		"InvalidParameter",
		"An operation parameter is not valid."
	},
	{
		WXF_INVALID_REPRESENTATION,
		WSXF_ACTION_FAULT,
		XML_NS_TRANSFER,
		FAULT_SENDER_CODE,
		"InvalidRepresentation",
		"The XML content is not valid."
	},
	{
		WSMAN_INVALID_SELECTORS,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_SENDER_CODE,
		"InvalidSelectors",
		"The Selectors for the resource are not valid."
	},
	{
		WSA_MESSAGE_INFORMATION_HEADER_REQUIRED,
		WSA_ACTION_FAULT,
		XML_NS_ADDRESSING,
		FAULT_SENDER_CODE,
		"MessageInformationHeaderRequired",
		"A required header is missing."
	},
	{
		WSMAN_NO_ACK,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_SENDER_CODE,
		"NoAck",
		"The receiver did not acknowledge the event delivery."
	},
	{
		WSMAN_QUOTA_LIMIT,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_SENDER_CODE,
		"QuotaLimit",
		"The service is busy servicing other requests."
	},
	{
		WSMAN_SCHEMA_VALIDATION_ERROR,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_SENDER_CODE,
		"SchemaValidationError",
		"The supplied SOAP violates the corresponding XML schema definition."
	},
	{
		WSEN_TIMED_OUT,
		WSENUM_ACTION_FAULT,
		XML_NS_ENUMERATION,
		FAULT_RECEIVER_CODE,
		"TimedOut",
		"The enumerator has timed out and is no longer valid."
	},
	{
		WSMAN_TIMED_OUT,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_RECEIVER_CODE,
		"TimedOut",
		"The operation has timed out."
	},
	{
		WSEN_UNSUPPORTED_EXPIRATION_TYPE,
		WSENUM_ACTION_FAULT,
		XML_NS_ENUMERATION,
		FAULT_RECEIVER_CODE,
		"UnsupportedExpirationType",
		"The specified expiration type is not supported."
	},
	{
		WSMAN_UNSUPPORTED_FEATURE,
		WSMAN_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_SENDER_CODE,
		"UnsupportedFeature",
		"The specified feature is not supported."
	},
	{
		WSMAN_UNSUPPORTED_FEATURE,
		WSMAN_ACTION_FAULT,
		XML_NS_CIM_BINDING,
		FAULT_RECEIVER_CODE,
		"PolymorphismModeNotSupported",
		"The specified feature is not supported."
	},
	{
    		WSMB_POLYMORPHISM_MODE_NOT_SUPPORTED,
		WSMB_ACTION_FAULT,
		XML_NS_WS_MAN,
		FAULT_RECEIVER_CODE,
		"UnsupportedFeature",
		"The specified feature is not supported."
	},
    	{
    		WSE_INVALID_EXPIRATION_TIME,
		WSMAN_ACTION_FAULT,
		XML_NS_EVENTING,
		FAULT_SENDER_CODE,
		"InvalidExpirationTime",
		"The expiration time is invalid"

    	},
	{
		WSMAN_UNKNOWN,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	}
};



void
wsman_set_fault( WsmanMessage *msg,
		WsmanFaultCodeType fault_code,
		WsmanFaultDetailType fault_detail_code,
		const char *details)
{
	if (!wsman_fault_occured(msg)) {
		msg->status.fault_code = fault_code;
		msg->status.fault_detail_code = fault_detail_code;
		if (details) msg->status.fault_msg = strdup(details);
	}
	return;
}

int
wsman_is_fault_envelope( WsXmlDocH doc )
{
	WsXmlNodeH node = ws_xml_get_child(ws_xml_get_soap_body(doc),
			0 , XML_NS_SOAP_1_2 , SOAP_FAULT);
	if ( node != NULL )
		return 1;
	else
		return 0;
}

WsmanKnownStatusCode
wsman_find_httpcode_for_value( WsXmlDocH doc )
{
	WsmanKnownStatusCode httpcode = 200;
	char *xp = ws_xml_get_xpath_value(doc, FAULT_XPATH_EXPR );
	if (xp != NULL) {
		if (strcmp(xp, FAULT_RECEIVER_CODE_NS) == 0 )
			httpcode = WSMAN_STATUS_INTERNAL_SERVER_ERROR;
		else if (strcmp(xp, FAULT_SENDER_CODE_NS) == 0 )
			httpcode = WSMAN_STATUS_BAD_REQUEST;
	}
	u_free(xp);
	return httpcode;
}


WsmanKnownStatusCode wsman_find_httpcode_for_fault_code( WsmanFaultCodeType faultCode )
{

	int i;
	WsmanKnownStatusCode httpcode = WSMAN_STATUS_INTERNAL_SERVER_ERROR;
	int nfaults = sizeof (fault_code_table) / sizeof (fault_code_table[0]);
	for (i = 0; i < nfaults; i++)
	{
		if (fault_code_table[i].fault_code == faultCode )
		{
			if (strcmp(fault_code_table[i].code, FAULT_RECEIVER_CODE ) == 0) {
				httpcode = WSMAN_STATUS_INTERNAL_SERVER_ERROR;
				break;
			}
			else if (strcmp(fault_code_table[i].code, FAULT_SENDER_CODE ) == 0) {
				httpcode = WSMAN_STATUS_BAD_REQUEST;
				break;
			}
			else if (strcmp(fault_code_table[i].code, FAULT_MUSTUNDERSTAND_CODE ) == 0) {
				httpcode = WSMAN_STATUS_BAD_REQUEST;
				break;
			}
		}
	}
	return httpcode;

}

WsXmlDocH
wsman_generate_fault( WsContextH cntx,
		WsXmlDocH in_doc,
		WsmanFaultCodeType faultCode,
		WsmanFaultDetailType faultDetail,
		char *fault_msg)
{
	int i;
	WsXmlDocH fault = NULL;
	char *reason, *detail;

	int nfaults = sizeof (fault_code_table) / sizeof (fault_code_table[0]);
	for (i = 0; i < nfaults; i++)
	{
		if (fault_code_table[i].fault_code == faultCode ) {
			if (fault_msg!= NULL ) {
				reason = fault_msg;
			} else {
				reason = fault_code_table[i].reason;
			}
			//debug("faultDetail: %d", faultDetail);
			if (faultDetail>0) {
				detail = fault_detail_table[faultDetail].detail;
				//debug("Fault detail: %s", fault_detail_table[faultDetail].detail);
			}
			else
				detail = NULL;

			fault =  wsman_create_fault_envelope(cntx, in_doc,
					fault_code_table[i].code,
					fault_code_table[i].subCodeNs,
					fault_code_table[i].subCode,
					fault_code_table[i].fault_action,
					NULL,
					reason,
					detail);
			break;
		}
	}
	return fault;
}



void
wsman_generate_fault_buffer ( WsContextH cntx,
		WsXmlDocH in_doc,
		WsmanFaultCodeType faultCode,
		WsmanFaultDetailType faultDetail,
		char * fault_msg,
		char **buf,
		int* len)
{

	WsXmlDocH doc = wsman_generate_fault(cntx, in_doc, faultCode, faultDetail, fault_msg);
	debug( "Fault Code: %d", faultCode);
	ws_xml_dump_memory_enc(doc, buf, len, NULL);
	ws_xml_destroy_doc(doc);
	return;
}





int
wsman_fault_occured(WsmanMessage *msg)
{
	return (msg->status.fault_code == WSMAN_RC_OK ) ?  0 : 1;
}




