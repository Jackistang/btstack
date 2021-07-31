#include "btstack_tlv.h"
#include "btstack_tlv_rtthread.h"
#include "utest.h"
#include <rtthread.h>

#define TAG(a,b,c,d) ( ((a)<<24) | ((b)<<16) | ((c)<<8) | (d) )

#define CHECK_EQUAL uassert_int_equal

static const btstack_tlv_t * btstack_tlv_impl;
static btstack_tlv_rtthread_t   btstack_tlv_context;

static rt_err_t utest_tc_init(void)
{
    btstack_tlv_impl = btstack_tlv_rtthread_init_instance(&btstack_tlv_context);

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void test_missing_tag(void)
{
	uint32_t tag = TAG('a','b','c','d');
	int size = btstack_tlv_impl->get_tag(&btstack_tlv_context, tag, NULL, 0);
	CHECK_EQUAL(size, 0);
}

static void test_write_read(void)
{
	uint32_t tag = TAG('a','b','c','d');
	uint8_t  data = 7;
	uint8_t  buffer = data;
	btstack_tlv_impl->store_tag(&btstack_tlv_context, tag, &buffer, 1);
	int size = btstack_tlv_impl->get_tag(&btstack_tlv_context, tag, NULL, 0);
	CHECK_EQUAL(size, 1);
	btstack_tlv_impl->get_tag(&btstack_tlv_context, tag, &buffer, 1);
	CHECK_EQUAL(buffer, data);
}

static void test_write_write_read(void)
{
	uint32_t tag = TAG('a','b','c','d');
	uint8_t  data = 7;
	uint8_t  buffer = data;
	btstack_tlv_impl->store_tag(&btstack_tlv_context, tag, &buffer, 1);
	data++;
	buffer = data;
	btstack_tlv_impl->store_tag(&btstack_tlv_context, tag, &buffer, 1);
	int size = btstack_tlv_impl->get_tag(&btstack_tlv_context, tag, NULL, 0);
	CHECK_EQUAL(size, 1);
	btstack_tlv_impl->get_tag(&btstack_tlv_context, tag, &buffer, 1);
	CHECK_EQUAL(buffer, data);
}

static void test_write_aba_read(void)
{
	uint32_t tag_a = TAG('a','a','a','a');
	uint32_t tag_b = TAG('b','b','b','b');;
	uint8_t  data = 7;
	uint8_t  buffer = data;
	btstack_tlv_impl->store_tag(&btstack_tlv_context, tag_a, &buffer, 1);
 	data++;
	buffer = data;
	btstack_tlv_impl->store_tag(&btstack_tlv_context, tag_b, &buffer, 1);
	data++;
	buffer = data;
	btstack_tlv_impl->store_tag(&btstack_tlv_context, tag_a, &buffer, 1);
	int size = btstack_tlv_impl->get_tag(&btstack_tlv_context, tag_a, NULL, 0);
	CHECK_EQUAL(size, 1);
	btstack_tlv_impl->get_tag(&btstack_tlv_context, tag_a, &buffer, 1);
	CHECK_EQUAL(buffer, data);
}

static void test_write_delete_read(void)
{
	uint32_t tag = TAG('a','b','c','d');
	uint8_t  data = 7;
	uint8_t  buffer = data;
	btstack_tlv_impl->store_tag(&btstack_tlv_context, tag, &buffer, 1);
	data++;
	buffer = data;
	btstack_tlv_impl->store_tag(&btstack_tlv_context, tag, &buffer, 1);
	btstack_tlv_impl->delete_tag(&btstack_tlv_context, tag);
	int size = btstack_tlv_impl->get_tag(&btstack_tlv_context, tag, NULL, 0);
	CHECK_EQUAL(size, 0);
}

static void test_migrate(void)
{
	uint32_t tag = TAG('a','b','c','d');
	uint8_t  data[8];
	memcpy(data, "01234567", 8);

	// entry 8 + data 8 = 16. 
	int i;
	for (i=0;i<8;i++){
		data[0] = '0' + i;
		btstack_tlv_impl->store_tag(&btstack_tlv_context, tag, &data[0], 8);
	}

	uint8_t buffer[8];
	btstack_tlv_impl->get_tag(&btstack_tlv_context, tag, &buffer[0], 1);
	CHECK_EQUAL(buffer[0], data[0]);
}

static void test_migrage2(void)
{
	uint32_t tag1 = 0x11223344;
	uint32_t tag2 = 0x44556677;
	uint8_t  data1[8];
	memcpy(data1, "01234567", 8);
	uint8_t  data2[8];
	memcpy(data2, "abcdefgh", 8);

	// entry 8 + data 8 = 16. 
	int i;
	for (i=0;i<8;i++){
		data1[0] = '0' + i;
		data2[0] = 'a' + i;
		btstack_tlv_impl->store_tag(&btstack_tlv_context, tag1, data1, 8);
		btstack_tlv_impl->store_tag(&btstack_tlv_context, tag2, data2, 8);
	}

	uint8_t buffer[8];
	btstack_tlv_impl->get_tag(&btstack_tlv_context, tag1, &buffer[0], 1);
	CHECK_EQUAL(buffer[0], data1[0]);
	btstack_tlv_impl->get_tag(&btstack_tlv_context, tag2, &buffer[0], 1);
	CHECK_EQUAL(buffer[0], data2[0]);
}

static void testcase_tlv_rtthread(void)
{
    UTEST_UNIT_RUN(test_missing_tag);
    UTEST_UNIT_RUN(test_write_read);
    UTEST_UNIT_RUN(test_write_write_read);
    UTEST_UNIT_RUN(test_write_aba_read);
    UTEST_UNIT_RUN(test_write_delete_read);
    UTEST_UNIT_RUN(test_migrate);
    UTEST_UNIT_RUN(test_migrage2);
}
UTEST_TC_EXPORT(testcase_tlv_rtthread, "btstack.tlv.rtthread", utest_tc_init, utest_tc_cleanup, 1000);
