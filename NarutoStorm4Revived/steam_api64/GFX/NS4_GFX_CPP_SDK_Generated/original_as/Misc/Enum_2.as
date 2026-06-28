package Enum
{
   public class Enum
   {
      
      private static var NextVal:Number = 0;
      
      private static var IsInit:Boolean = false;
      
      public function Enum()
      {
         super();
         if(IsInit == true)
         {
            trace("new でこのクラスを生成しないで下さい.");
            trace("public static で関数を定義しているのでそちらを使ってください.");
            return;
         }
         IsInit = true;
      }
      
      public static function Next(param1:Number = NaN) : Number
      {
         if(isNaN(param1) == false)
         {
            NextVal = param1;
         }
         else
         {
            ++NextVal;
         }
         return NextVal;
      }
   }
}

