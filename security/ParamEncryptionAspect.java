package edu.usc.csci310.project.security;

import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import edu.usc.csci310.project.security.CryptoConverter;

@Aspect
@Component
public class ParamEncryptionAspect {

    @Autowired
    private CryptoConverter cryptoService;

    @Around("@annotation(encryptParams)")
    public Object encryptParams(ProceedingJoinPoint joinPoint, EncryptParams encryptParams) throws Throwable {
        Object[] args = joinPoint.getArgs();
        for (int i = 0; i < args.length; i++) {
            if (args[i] instanceof String param) {
                if (!param.isEmpty()) {
                    args[i] = cryptoService.convertToDatabaseColumn(param);
                }
            }
        }
        return joinPoint.proceed(args);
    }
}
