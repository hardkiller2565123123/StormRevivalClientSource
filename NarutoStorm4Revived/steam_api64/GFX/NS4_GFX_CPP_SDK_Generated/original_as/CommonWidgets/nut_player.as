package script.duel_cmn
{
   import flash.display.MovieClip;
   import script.msg_match_s_txt.all_nut;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol287")]
   public class nut_player extends MovieClip
   {
      
      public var mc_player:script.msg_match_s_txt.all_nut;
      
      public function nut_player()
      {
         super();
         this.visible = false;
         this.stop();
      }
      
      public function SetVisible(param1:Boolean) : *
      {
         this.visible = param1;
      }
      
      public function SetPadNum(param1:int) : *
      {
         var _loc2_:MovieClip = MovieClip(this["mc_player"]);
         if(_loc2_)
         {
            _loc2_.gotoAndStop(param1);
         }
      }
      
      public function SetPos(param1:Number, param2:Number) : *
      {
         this.x = param1;
         this.y = param2;
      }
   }
}

