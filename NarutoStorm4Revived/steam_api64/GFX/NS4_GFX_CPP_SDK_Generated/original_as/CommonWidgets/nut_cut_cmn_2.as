package script.duel_cutin3
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import script.msg_round_lang.anm_go;
   import script.msg_round_lang.anm_round;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public class nut_cut_cmn extends MovieClip
   {
      
      public var mc_go:anm_go;
      
      public var all_cutin_msg:anm_round;
      
      public var mc_round:anm_round;
      
      public var SetActive:Function;
      
      public function nut_cut_cmn()
      {
         super();
         addFrameScript(35,this.frame36,64,this.frame65);
         this.stop();
      }
      
      public function CreateRoundCutin(param1:int) : *
      {
         this.gotoAndPlay("in");
         var _loc2_:anm_round = anm_round(getChildByName("mc_round"));
         _loc2_.SetRoundNum(param1);
         this.SetActive(true);
      }
      
      public function IsEndRoundAnm() : Boolean
      {
         return currentLabel == "round_end" ? true : false;
      }
      
      public function StarWatchtCutin() : *
      {
         addEventListener(Event.ENTER_FRAME,this.UpdateRoundCutin);
      }
      
      public function UpdateRoundCutin() : *
      {
         if(this.currentLabel == "end")
         {
            this.SetActive(false);
            removeEventListener(Event.ENTER_FRAME,this.UpdateRoundCutin);
         }
      }
      
      internal function frame36() : *
      {
         stop();
      }
      
      internal function frame65() : *
      {
         this.stop();
      }
   }
}

