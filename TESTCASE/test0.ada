WITH TEXT_IO; USE TEXT_IO;

PROCEDURE BeginSamples IS BEGIN
   BEGIN
      PUT_LINE("Bonjour A");
   END;
   FOR I IN 1..3 LOOP 
      BEGIN
         PUT_LINE("Bonjour B");
      END;
   END LOOP;
   BEGIN
      PUT_LINE("Bonjour C");
   END;    
END BeginSamples;
