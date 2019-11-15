#ifndef libzkfv_errdef_h
#define libzkfv_errdef_h

/**
*	@file		libzkfverrdef.h
*	@brief		指静脉SDK-错误码定义
*	@author		scar chen
*	@date		2016-01-26
*	@version	1.0
*	@par	版权：
*				ZKTeco
*	@par	历史版本			
*
*	@note
*
*/

#define ZKFV_ERR_ALREADY_INIT	1	/**<	已经初始化 */
#define ZKFV_ERR_OK			0	/**<	操作成功 */
#define ZKFV_ERR_INITLIB	-1	/**<	初始化算法库失败 */
#define ZKFV_ERR_INIT		-2	/**<	初始化采集库失败 */
#define ZKFV_ERR_NO_DEVICE	-3	/**<	无设备连接 */
#define ZKFV_ERR_NOT_SUPPORT	-4	/**<	接口暂不支持 */
#define ZKFV_ERR_INVALID_PARAM	-5	/**<	无效参数 */
#define ZKFV_ERR_OPEN			-6	/**<	打开设备失败 */
#define ZKFV_ERR_INVALID_HANDLE	-7	/**<	无效句柄 */
#define ZKFV_ERR_CAPTURE		-8	/**<	取像失败 */
#define ZKFV_ERR_EXTRACT_FP		-9	/**<	提取指纹模板失败 */
#define ZKFV_ERR_ABSORT			-10	/**<	中断 */
#define ZKFV_ERR_MEMORY_NOT_ENOUGH			-11	/**<	内存不足 */
#define ZKFV_ERR_BUSY			-12	/**<	当前正在采集 */
#define ZKFV_ERR_ADD_FINGER		-13	/**<	添加指纹模板失败 */
#define ZKFV_ERR_DEL_FINGER		-14	/**<	删除指纹失败 */
#define ZKFV_ERR_ADD_VEIN		-15	/**<	添加静脉模板失败 */
#define ZKFV_ERR_DEL_VEIN		-16	/**<	删除静脉纹失败 */
#define ZKFV_ERR_FAIL			-17	/**<	操作失败 */
#define ZKFV_ERR_CANCEL			-18	/**<	取消采集 */
#define ZKFV_ERR_EXTRACT_FV		-19	/**<	提取指静脉模板失败 */
#define ZKFV_ERR_VERIFY_FP		-20 /**<	比对指纹失败 */
#define ZKFV_ERR_VERIFY_FV		-21 /**<	比对指静脉失败 */
#define ZKFV_ERR_MERGE			-22 /**<	合并登记指纹模板失败	*/
#define ZKFV_ERR_FP_EXIST		-23	/**<	重复指纹ID	*/
#define ZKFV_ERR_FPTEMPLATE	    -24	/**<	指纹模板异常 */
#define ZKFV_ERR_FVTEMPLATE	    -25	/**<	静脉模板异常 */

#endif