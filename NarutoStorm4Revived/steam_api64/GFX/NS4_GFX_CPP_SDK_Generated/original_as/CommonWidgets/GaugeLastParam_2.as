package script.gauge_last
{
   import Enum.Enum;
   
   public class GaugeLastParam
   {
      
      public static const CCD_FACE_ICON_SET_0:int = Enum.Next(0);
      
      public static const CCD_FACE_ICON_SET_1:int = Enum.Next();
      
      public static const CCD_FACE_ICON_SET_2:int = Enum.Next();
      
      public static const CCD_FACE_ICON_SET_3:int = Enum.Next();
      
      public static const CCD_FACE_ICON_SET_NUM:int = Enum.Next();
      
      public static const CCD_FACE_ICON_TBL:Array = [["nrt9","nrt4","nrt_awk1","nrt0"],["ssk11","ssk6","ssk_awk1","ssk0"]];
      
      public static const CCD_NAME_ICON_TBL:Array = ["nrt1","ssk1"];
      
      public function GaugeLastParam()
      {
         super();
      }
   }
}

