package script.msg_round_lang
{
   import flash.display.MovieClip;
   import script.num_l.nut_num_l;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol10")]
   public class anm_round extends MovieClip
   {
      
      public var mc_msg1:MovieClip;
      
      public var mc_msg2:MovieClip;
      
      public var mc_num1:nut_num_l;
      
      public var mc_num10:nut_num_l;
      
      public var mc_num100:nut_num_l;
      
      public function anm_round()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4);
      }
      
      public function SetRoundNum(param1:int) : *
      {
         var _loc2_:int = param1 / 100;
         var _loc3_:int = (param1 - _loc2_ * 100) / 10;
         var _loc4_:int = param1 % 10;
         var _loc5_:MovieClip = MovieClip(getChildByName("mc_num100"));
         var _loc6_:MovieClip = MovieClip(getChildByName("mc_num10"));
         var _loc7_:MovieClip = MovieClip(getChildByName("mc_num1"));
         if(param1 == 999)
         {
            this.gotoAndStop("txt_other");
         }
         else if(param1 >= 100)
         {
            this.gotoAndStop("match_100");
            if(_loc5_ != null)
            {
               _loc5_.gotoAndStop(_loc2_ + 1);
            }
            if(_loc6_ != null)
            {
               _loc6_.gotoAndStop(_loc3_ + 1);
            }
            if(_loc7_ != null)
            {
               _loc7_.gotoAndStop(_loc4_ + 1);
            }
         }
         else if(param1 >= 100)
         {
            this.gotoAndStop("match_10");
            if(_loc6_ != null)
            {
               _loc6_.gotoAndStop(_loc3_ + 1);
            }
            if(_loc7_ != null)
            {
               _loc7_.gotoAndStop(_loc4_ + 1);
            }
         }
         else
         {
            this.gotoAndStop("match_1");
            if(_loc7_ != null)
            {
               _loc7_.gotoAndStop(_loc4_ + 1);
            }
         }
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame2() : *
      {
         this.stop();
      }
      
      internal function frame3() : *
      {
         this.stop();
      }
      
      internal function frame4() : *
      {
         this.stop();
      }
   }
}

