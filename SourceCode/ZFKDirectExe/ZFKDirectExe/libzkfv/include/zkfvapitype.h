#ifndef libzkfv_type_h
#define libzkfv_type_h

/**
*	@file		libzkfvtype.h
*	@brief		指静脉SDK-结构体定义
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



#ifndef MAX_TEMPLATE_SIZE
#define MAX_TEMPLATE_SIZE 2048		/**<	模板最大长度 */
#endif

#ifndef MAX_FVTEMPLATE_COUNT
#define MAX_FVTEMPLATE_COUNT	6	/**<	最大指静脉模板数 */
#endif

#define FP_THRESHOLD_CODE		1	/**<	指纹1:1阀值 */
#define FP_MTHRESHOLD_CODE		2	/**<	指纹1:N阀值 */
#define FV_THRESHOLD_CODE		3	/**<	指静脉1:1阀值 */
#define FV_MTHRESHOLD_CODE		4	/**<	指静脉1:N阀值 */

#define BIO_TYPE_FP				0	/**<	生物识别类型:指纹	*/
#define BIO_TYPE_FV				1	/**<	生物识别类型:指静脉	*/

#define IDENTIFY_MODE_ANY		0	/**<	混合比对模式-高通过率	*/
#define IDENTIFY_MODE_FAKE		1	/**<	混合比对模式-防假模式	*/
#define IDENTIFY_MODE_BOTH		2	/**<	混合比对模式-安全模式	*/

#endif