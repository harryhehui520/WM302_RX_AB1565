/* Copyright Statement:
 *
 * (C) 2020  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("Airoha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
 * if you have agreed to and been bound by the applicable license agreement with
 * Airoha ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of Airoha Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */

#include "iAP2_log.h"

ATTR_LOG_STRING_LIB IAP2_001[] = LOG_INFO_PREFIX(IAP2)"[IAP2]iap2_connect, status: 0x%x\r\n";
ATTR_LOG_STRING_LIB IAP2_002[] = LOG_INFO_PREFIX(IAP2)"[IAP2]iap2_disconnect, iap2_state: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_003[] = LOG_INFO_PREFIX(IAP2)"[iAP2]register_cb callback %x\r\n";
ATTR_LOG_STRING_LIB IAP2_004[] = LOG_INFO_PREFIX(IAP2)"[iAP2]all are in use, please extend the value of IAP2_APP_SUPPORT_CB_MAX_NUM\r\n";
ATTR_LOG_STRING_LIB IAP2_005[] = LOG_INFO_PREFIX(IAP2)"[iAP2]deregister_cb callback %x\r\n";
ATTR_LOG_STRING_LIB IAP2_006[] = LOG_INFO_PREFIX(IAP2)"[iAP2]delete fail, because of not find the callback\r\n";
ATTR_LOG_STRING_LIB IAP2_007[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_send_data_by_external_accessory_session, status: 0x%x\r\n";
ATTR_LOG_STRING_LIB IAP2_008[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_send_data_by_control_session, status: 0x%x\r\n";
ATTR_LOG_STRING_LIB IAP2_009[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_event_callback, event: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_010[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_hold_data, session type %d is not support!\r\n";
ATTR_LOG_STRING_LIB IAP2_011[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_release_data, session type %d is not support!\r\n";
ATTR_LOG_STRING_LIB IAP2_012[] = LOG_INFO_PREFIX(IAP2)"[iAP2] iap2 send app launch request fail, oom!\r\n";
ATTR_LOG_STRING_LIB IAP2_013[] = LOG_INFO_PREFIX(IAP2)"[iAP2] iap2 send app launch request, status:%d, is_alert:%d\r\n";

ATTR_LOG_STRING_LIB IAP2_SPP_001[] = LOG_INFO_PREFIX(IAP2)"[IAP2]iap2_create_list fail, because of no memory\r\n";
ATTR_LOG_STRING_LIB IAP2_SPP_002[] = LOG_INFO_PREFIX(IAP2)"[IAP2]bt_iap2_init, result: 0x%4x\r\n";
ATTR_LOG_STRING_LIB IAP2_SPP_003[] = LOG_INFO_PREFIX(IAP2)"[IAP2]bt_iap2_connect fail, not first conencted and not reconnect!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPP_004[] = LOG_INFO_PREFIX(IAP2)"[IAP2]bt_iap2_connect, status: 0x%x\r\n";
ATTR_LOG_STRING_LIB IAP2_SPP_005[] = LOG_INFO_PREFIX(IAP2)"[IAP2]bt_iap2_event_callback, msg: 0x%4x, status: 0x%4x\r\n";
ATTR_LOG_STRING_LIB IAP2_SPP_006[] = LOG_INFO_PREFIX(IAP2)"[IAP2]BT_SPP_CONNECT_IND, handle: 0x%4x, channel_id: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_SPP_007[] = LOG_INFO_PREFIX(IAP2)"[IAP2]BT_SPP_CONNECT_CNF, link info cannot find!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPP_008[] = LOG_INFO_PREFIX(IAP2)"[IAP2]BT_SPP_CONNECT_CNF, Wrong spp handle!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPP_009[] = LOG_INFO_PREFIX(IAP2)"[IAP2]BT_SPP_DISCONNECT_IND, Wrong spp handle!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPP_010[] = LOG_INFO_PREFIX(IAP2)"[IAP2]bt_iap2_event_callback, recieved data point: 0x%4x\r\n";
ATTR_LOG_STRING_LIB IAP2_SPP_011[] = LOG_INFO_PREFIX(IAP2)"[IAP2]bt_iap2_hold_data, hold data point: 0x%4x\r\n";
ATTR_LOG_STRING_LIB IAP2_SPP_012[] = LOG_INFO_PREFIX(IAP2)"[IAP2]bt_iap2_release_data, hold data point: 0x%4x\r\n";
ATTR_LOG_STRING_LIB IAP2_SPP_013[] = LOG_INFO_PREFIX(IAP2)"[IAP2]bt_iap2_spp, unknown device, status: 0x%8x\r\n";
ATTR_LOG_STRING_LIB IAP2_TASK_001[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_task_mfi_data_handler, linkIndex: 0x%2x, data point is 0x%4x, len is %d\r\n";
ATTR_LOG_STRING_LIB IAP2_TASK_002[] = LOG_INFO_PREFIX(IAP2)"[IAP2]iap2_task_mfi_data_handler message:0x%4x, length is 0x%2x\r\n";
ATTR_LOG_STRING_LIB IAP2_TASK_003[] = LOG_INFO_PREFIX(IAP2)"[IAP2]iap2_task_mfi_data_handler, cannot alloc memory!\r\n";
ATTR_LOG_STRING_LIB IAP2_TASK_004[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_task_mfi_data_handler, free packet\r\n";
ATTR_LOG_STRING_LIB IAP2_TASK_005[] = LOG_INFO_PREFIX(IAP2)"[IAP2]create service queue failed!\r\n";
ATTR_LOG_STRING_LIB IAP2_TASK_006[] = LOG_INFO_PREFIX(IAP2)"[IAP2]service recieve message:type is %d\r\n";
ATTR_LOG_STRING_LIB IAP2_TASK_007[] = LOG_INFO_PREFIX(IAP2)"[IAP2]iap2_task_init, fail!\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_001[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_dump_linkInfo, state: %d, txSEQ: %d, rxSEQ: %d, "
                                      "rxCumulative: %d, maxCumulative: %d, rxCumulativeTimeout: %d, "
                                      "rxCumulativeTimer: 0x%4x, SNWindowRange: %d, retransmission_timeout: 0x%4x, "
                                      "max_packet_length: 0x%4x\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_002[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_dump_headerInfo, packet_start: 0x%x, packet_length: 0x%x, ctrl_byte: 0x%x, "
                                      "seq_number: %d, ack_number: %d, session_identifier: %d, header_checksum: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_003[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_dump_syncInfo, link_version: %d, max_num_out_packets: %d, "
                                      "max_packet_length: 0x%x, retransmission_timeout: 0x%x, "
                                      "cumulative_ack_timeout: 0x%x, max_retrans: %d, max_cumulative_ack: %d, "
                                      "session_0.id: %d, session_0.type, session_0.version, "
                                      "session_1.id: %d, session_1.type, session_1.version\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_004[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_dump_ctrlSession_header, start: 0x%x, length: 0x%x, msg_id: 0x%x\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_005[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_dump_ctrlSession_params, length: 0x%x, param_id: 0x%x, param: %s\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_006[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_check_uuid_is_valid, valid\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_007[] = LOG_INFO_PREFIX(IAP2)"[IAP2] TX queue number of nodes is %d\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_008[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_memory_alloc, ptr: 0x%x, size: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_009[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_memory_alloc, fail\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_010[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_memory_free, ptr: 0x%x\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_011[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_timer_expire, timer: 0x%4x, duration: %d ms\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_012[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_set_timer, start timer: 0x%4x, delay: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_013[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_set_timer, create timer fail\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_014[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_set_timer, reset timer: 0x%4x, delay: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_015[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_release_timer, timer: 0x%x\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_016[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_release_timer, timer: 0x%x has been released\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_017[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_check_timer_is_expired, Yes\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_018[] = LOG_INFO_PREFIX(IAP2)"[IAP2]iap2_add_node, fail!\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_019[] = LOG_INFO_PREFIX(IAP2)"[IAP2]iap2_delete_node, node: 0x%4x, packet: 0x%4x, pak_len: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_020[] = LOG_INFO_PREFIX(IAP2)"[IAP2]iap2_find_node_by_index, node not find!\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_021[] = LOG_INFO_PREFIX(IAP2)"[IAP2]iap2_find_node_by_index, find node: 0x%4x, packet: 0x%4x, pak_len: 0x%4x\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_022[] = LOG_INFO_PREFIX(IAP2)"[IAP2]iap2_check_node_buffer, count: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_023[] = LOG_INFO_PREFIX(IAP2)"[IAP2]iap2_check_node_buffer, pak: 0x%4x, pak_len: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_UTIL_024[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_release_timer OK, timer: 0x%x\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_001[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_check_packet_validity, length invalid !\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_002[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_check_packet_validity, packet_start invalid !\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_003[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_check_packet_validity, header checksum invalid !\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_004[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_check_packet_validity, payload checksum invalid !\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_005[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_check_packet_validity, state invalid !\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_006[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_check_packet_validity, SNWindowRange is %d\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_007[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_check_packet_validity, ACK retransmission packet, seq 0x%2x, rxseq 0x%2x\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_008[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_check_packet_validity, sequence number invalid !\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_009[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_check_packet_validity, maxCumulative reach!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_010[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_check_packet_validity, valid, OK!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_011[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_check_negotiable_link_parameters, success\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_012[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_check_negotiable_link_parameters, Fail!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_013[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_start_extA_protocol, protocolIdentifier: %d, session_id: 0x%x\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_014[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_stop_extA_protocol, session_id is %d\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_015[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_stop_extA_protocol, free packet\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_016[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_ctrlSession_packet_handler, free packet\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_017[] = LOG_INFO_PREFIX(IAP2)"[IAP2] packet is invalid, free packet\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_018[] = LOG_INFO_PREFIX(IAP2)"[IAP2] packet is invalid, free packet\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_019[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_get_packet_length, not iAP2 packet!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_020[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_release_packets, Wrong index!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_021[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_rx_queue_handler, g_offset is %d, data_len is %d\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_022[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_rx_queue_handler, not iAP2 packet!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_023[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_rx_queue_handler, data_check_flag is %d\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_024[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_rx_queue_handler, Heap Memory OOM!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_025[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_rx_queue_handler, Heap Memory OOM!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_026[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_rx_queue_handler, not find the continue packet, wait\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_027[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_rx_queue_handler, wait for the continue payload!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_028[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_rx_queue_handler, Heap Memory OOM!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_029[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_rx_data_pre_check, Not find any packet exist!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_030[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_data_handler, data_len: 0x%x, state: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_031[] = LOG_INFO_PREFIX(IAP2)"[IAP2] The remote device can not support iAP2\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_032[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_control_session_handler, free packet\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_033[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_read_certificate_data, fail, ret: 0x%x\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_034[] = LOG_INFO_PREFIX(IAP2)"[IAP2] activation M2 Mfi_crt len: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_035[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_read_challenge_data\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_036[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_write_challenge_data, param_length: 0x%x \r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_037[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_write_challenge_data, payload_length: %d \r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_038[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_get_challenge_data, ret: 0x%x, length: %d \r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_039[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_gen_challenge_response, fail, ret: 0x%x\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_040[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_send_identification, ori_length: %d, total_length: %d, id: 0x%x\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_041[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_send_identification, end!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_042[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_state_handler, state: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_043[] = LOG_INFO_PREFIX(IAP2)"[IAP2] The remote device can not support iAP2\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_044[] = LOG_INFO_PREFIX(IAP2)"[IAP2] detect begin, txSeq: %d, state: %d, detectCount: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_045[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_send_ea_session_data, lastAckPSN is %d, txseq is %d\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_046[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_send_ctrl_session_data, message_id: 0x%x, data_size: 0x%x, state: %d\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_047[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_rx_data_handler, unknown state!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_048[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_clear_linkInfo\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_049[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_find_end_packet_index, target_len is %d, current_len is %d\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_050[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_find_end_packet_index, continue packet index is %d\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_051[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_rx_queue_handler, node count is %d\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_052[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_rx_queue_handler, IAP2_DATA_LENGTH_MORE handle done!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_053[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_rx_queue_handler, IAP2_DATA_LENGTH_MORE handle continue!\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_054[] = LOG_INFO_PREFIX(IAP2)"iap2_write_challenge_data \r\n ";
ATTR_LOG_STRING_LIB IAP2_SPEC_055[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_timer_handler, timer: 0x%4x, duration: %d ms\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_056[] = LOG_INFO_PREFIX(IAP2)"[IAP2] iap2_timer_handler, all duration: %d ms\r\n";
ATTR_LOG_STRING_LIB IAP2_SPEC_057[] = LOG_INFO_PREFIX(IAP2)"[IAP2] invalid link sync packet !\r\n";
ATTR_LOG_STRING_LIB IAP2_RHO_001[] = LOG_INFO_PREFIX(IAP2)"[IAP2][RHO] allow execution:0x%x, allow execution ext:0x%x";
ATTR_LOG_STRING_LIB IAP2_RHO_002[] = LOG_INFO_PREFIX(IAP2)"[IAP2][RHO] get data length:0x%x";
ATTR_LOG_STRING_LIB IAP2_RHO_003[] = LOG_INFO_PREFIX(IAP2)"[IAP2][RHO] get data status:0x%x";
ATTR_LOG_STRING_LIB IAP2_RHO_004[] = LOG_INFO_PREFIX(IAP2)"[IAP2][RHO] get data: data is NULL or iAP2 not connected!";
ATTR_LOG_STRING_LIB IAP2_RHO_005[] = LOG_INFO_PREFIX(IAP2)"[IAP2][RHO] update, Agent->Partner success.";
ATTR_LOG_STRING_LIB IAP2_RHO_006[] = LOG_INFO_PREFIX(IAP2)"[IAP2][RHO] update, Partner->Agent success.";
ATTR_LOG_STRING_LIB IAP2_RHO_007[] = LOG_INFO_PREFIX(IAP2)"[IAP2][RHO] update, data is NULL!";
ATTR_LOG_STRING_LIB IAP2_RHO_008[] = LOG_INFO_PREFIX(IAP2)"[IAP2][RHO] update, unknown role:0x%x";
ATTR_LOG_STRING_LIB IAP2_RHO_009[] = LOG_INFO_PREFIX(IAP2)"[IAP2][RHO] status callback, role:0x%x event:0x%x status:0x%x";

