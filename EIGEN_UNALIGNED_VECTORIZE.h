#pragma once
/*
���ھ����Ƿ������δ�����ڴ���SIMDʸ�������������������Ϊ 1����˼�ǣ�
        ����ʹ���ݲ����ϸ� 16 �ֽڣ�SSE����32 �ֽڣ�AVX�����룬
        Eigen ��Ȼ���ö�Ӧ�� unaligned load/store ָ����������������

�ִ�X86Ӳ������Intel Core 2���Ժ�AMD Zenϵ�У���unaligned load������ļ�С��������alignedû���𣬽��SIMDӦ�ó���
*/
#define EIGEN_UNALIGNED_VECTORIZE 1