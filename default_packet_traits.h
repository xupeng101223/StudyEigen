#pragma once
struct default_packet_traits
{
        enum {
                HasHalfPacket = 0,

                HasAdd = 1,
                HasSub = 1,
                HasShift = 1,
                HasMul = 1,
                HasNegate = 1,
                HasAbs = 1,
                HasArg = 0,
                HasAbs2 = 1,
                HasAbsDiff = 0,
                HasMin = 1,
                HasMax = 1,
                HasConj = 1,
                HasSetLinear = 1,
                HasBlend = 0,

                // 该标志用于表示是否支持分组比较
                // pcmp_eq、pcmp_lt和pcmp_le应该被定义为true。
                HasCmp = 0,

                HasDiv = 0,
                HasSqrt = 0,
                HasRsqrt = 0,
                HasExp = 0,
                HasExpm1 = 0,
                HasLog = 0,
                HasLog1p = 0,
                HasLog10 = 0,
                HasPow = 0,

                HasSin = 0,
                HasCos = 0,
                HasTan = 0,
                HasASin = 0,
                HasACos = 0,
                HasATan = 0,
                HasSinh = 0,
                HasCosh = 0,
                HasTanh = 0,
                HasLGamma = 0,
                HasDiGamma = 0,
                HasZeta = 0,
                HasPolygamma = 0,
                HasErf = 0,
                HasErfc = 0,
                HasNdtri = 0,
                HasBessel = 0,
                HasIGamma = 0,
                HasIGammaDerA = 0,
                HasGammaSampleDerAlpha = 0,
                HasIGammac = 0,
                HasBetaInc = 0,

                HasRound = 0,
                HasRint = 0,
                HasFloor = 0,
                HasCeil = 0,
                HasSign = 0
        };
};