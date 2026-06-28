package script.map_l
{
   import Enum.Enum;
   
   public class WorldMapParam
   {
      
      public static const CCD_MAP_AREA_ICON_TBL:Array = ["all_mark01","all_mark02","all_mark03","all_mark04","all_mark05","all_mark06","all_mark07","all_mark08","all_mark09","all_mark10","all_mark11","all_mark12","all_mark13","all_mark14","all_mark15","all_mark16","all_mark17"];
      
      public static const CCD_MAP_AREA_NAME_TBL:Array = ["map_telop_003","map_icon_008","c_sta_15","map_icon_025","map_icon_018","map_telop_001","c_sta_17","c_sta_22","map_telop_000","c_sta_48","map_icon_017","map_telop_102","map_icon_016","map_telop_002","map_telop_019","map_telop_004","map_icon_026"];
      
      public static const CCD_CURSOR_TBL:Array = [[0,2,1,2],[0,5,1,0],[0,3,0,6],[2,4,1,6],[3,5,5,6],[4,5,1,4],[7,10,2,7],[7,8,6,11],[7,12,6,11],[11,16,12,16],[6,10,4,12],[15,9,8,15],[8,10,10,9],[13,15,15,14],[13,16,13,14],[13,16,11,13],[15,16,9,14]];
      
      public static const IDX_UP:int = Enum.Next(0);
      
      public static const IDX_DOWN:int = Enum.Next();
      
      public static const IDX_LEFT:int = Enum.Next();
      
      public static const IDX_RIGHT:int = Enum.Next();
      
      public function WorldMapParam()
      {
         super();
      }
   }
}

