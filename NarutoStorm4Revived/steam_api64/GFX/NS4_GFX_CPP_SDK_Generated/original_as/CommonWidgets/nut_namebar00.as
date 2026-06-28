package script.freebtl_namebar
{
   import flash.display.MovieClip;
   
   public class nut_namebar00 extends MovieClip
   {
      
      public const PLAYER_1P:String = "1P";
      
      public const PLAYER_2P:String = "2P";
      
      public const PLAYER_3P:String = "3P";
      
      public const PLAYER_4P:String = "4P";
      
      public const PLAYER_5P:String = "5P";
      
      public const PLAYER_6P:String = "6P";
      
      public const PLAYER_7P:String = "7P";
      
      public const PLAYER_8P:String = "8P";
      
      public const PLAYER_COM:String = "COM";
      
      public function nut_namebar00()
      {
         super();
      }
      
      public function setSelect(param1:Boolean) : void
      {
         if(param1)
         {
            gotoAndStop("on");
         }
         else
         {
            gotoAndStop("nomal");
         }
      }
      
      public function setDark(param1:Boolean, param2:Boolean) : void
      {
         if(param1)
         {
            if(param2)
            {
               gotoAndPlay("bad_in");
            }
            else
            {
               gotoAndPlay("dark_in");
            }
         }
         else if(param2)
         {
            gotoAndStop("bad");
         }
         else
         {
            gotoAndStop("dark");
         }
      }
      
      public function isEndDark() : Boolean
      {
         if(currentFrameLabel == "bad" || currentFrameLabel == "dark")
         {
            return true;
         }
         return false;
      }
      
      public function setDispFace(param1:Boolean) : void
      {
         var _loc2_:MovieClip = getChildByName("all_charicon_s") as MovieClip;
         if(_loc2_ != null)
         {
            _loc2_.visible = param1;
         }
      }
      
      public function setFace(param1:String) : void
      {
         trace("call nut_nambar00::setFace( " + param1 + " )");
         var _loc2_:MovieClip = getChildByName("all_charicon_s") as MovieClip;
         if(_loc2_ != null)
         {
            _loc2_.gotoAndStop(param1);
         }
      }
      
      public function setPlayerIcon(param1:String) : void
      {
         var _loc2_:MovieClip = getChildByName("mc_player_s") as MovieClip;
         if(_loc2_ != null)
         {
            _loc2_.gotoAndStop(param1);
         }
      }
      
      public function setPlayerIconByNum(param1:Number) : void
      {
         var _loc2_:Array = ["COM","1P","2P","3P","4P","5P","6P","7P","8P"];
         var _loc3_:MovieClip = getChildByName("mc_player_s") as MovieClip;
         if(_loc3_ != null)
         {
            _loc3_.gotoAndStop(_loc2_[param1]);
         }
      }
   }
}

