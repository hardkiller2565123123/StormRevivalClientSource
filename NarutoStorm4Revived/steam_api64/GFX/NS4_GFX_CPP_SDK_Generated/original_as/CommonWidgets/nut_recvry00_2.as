package script.cutin_rcvry
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.ExternalInterface;
   import script.cutin_rcvry_lang.nut_rcvry_msg;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public class nut_recvry00 extends MovieClip
   {
      
      public var all_recvry_txt:nut_recvry_txt;
      
      public var all_resultbar00:nut_resultbar00;
      
      public var all_resultbar01:nut_resultbar00;
      
      public var dmy_gauge:MovieClip;
      
      public var mc_bonus_bg:MovieClip;
      
      public var mc_rcvry_title:nut_rcvry_msg;
      
      public var GetParam:Function;
      
      public var GetRateString:Function;
      
      public var GetRankString:Function;
      
      public var SetEnd:Function;
      
      public var UpdateGaugePos:Function;
      
      public var SetOutEnd:Function;
      
      private const STATE_NONE:* = -1;
      
      private const STATE_INIT:* = 0;
      
      private const STATE_ANM_START:* = 1;
      
      private const STATE_ANM_WAIT:* = 2;
      
      private const STATE_END_WAIT:* = 3;
      
      private const STATE_WAIT:* = 4;
      
      private const STATE_OUT_WAIT:* = 5;
      
      private const STATE_END:* = 6;
      
      private var time_rate:int;
      
      private var rank_rate:int;
      
      private var life:Number;
      
      private var name_code:String;
      
      private var face_code:String;
      
      private var m_state:int;
      
      private var m_step:int;
      
      public function nut_recvry00()
      {
         super();
         addFrameScript(23,this.frame24,36,this.frame37);
         trace("init nut_recvry00");
         this.time_rate = 0;
         this.rank_rate = 0;
         this.life = 100;
         this.name_code = "";
         this.face_code = "";
         this.m_state = this.STATE_INIT;
         this.m_step = 0;
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
      }
      
      private function onEnterFrameCtrl(param1:Event) : void
      {
         var _loc2_:Object = null;
         var _loc3_:Object = null;
         var _loc4_:* = undefined;
         var _loc5_:int = 0;
         var _loc6_:MovieClip = null;
         var _loc7_:Object = null;
         switch(this.m_state)
         {
            case this.STATE_INIT:
               trace("---STATE_INIT");
               _loc2_ = new Object();
               _loc2_.time = this.time_rate;
               _loc2_.rank = this.rank_rate;
               this.GetParam(_loc2_);
               this.time_rate = _loc2_.time;
               this.rank_rate = _loc2_.rank;
               this.m_state = this.STATE_ANM_START;
               break;
            case this.STATE_ANM_START:
               trace("---STATE_ANM_START");
               _loc3_ = new Object();
               _loc3_.str = "";
               this.all_resultbar00.txt_title00.SetText(String(ExternalInterface.call("MessageConvert","battleresult_003")));
               this.all_resultbar00.txt_rank00.visible = false;
               this.GetRateString(this.time_rate,_loc3_);
               trace("arg.str = " + _loc3_.str);
               this.all_resultbar00.txt_per00.SetText(_loc3_.str);
               this.GetRankString(0,_loc3_);
               _loc4_ = _loc3_.str;
               trace("arg.str = " + _loc3_.str);
               this.all_resultbar01.txt_title00.SetText(_loc3_.str);
               this.all_resultbar01.txt_rank00.SetText(" ");
               this.GetRateString(this.rank_rate,_loc3_);
               trace("arg.str = " + _loc3_.str);
               this.all_resultbar01.txt_per00.SetText(_loc3_.str);
               _loc5_ = this.time_rate + this.rank_rate;
               this.all_recvry_txt.txt_recvry00.SetText(String(ExternalInterface.call("MessageConvert","Survival_sys_003")));
               this.GetRateString(_loc5_,_loc3_);
               trace("arg.str = " + _loc3_.str);
               this.all_recvry_txt.txt_recvry_per.SetText(_loc3_.str);
               gotoAndPlay("in");
               this.m_state = this.STATE_ANM_WAIT;
               break;
            case this.STATE_ANM_WAIT:
               _loc6_ = getChildByName("dmy_gauge") as MovieClip;
               if(_loc6_ != null)
               {
                  _loc7_ = new Object();
                  _loc7_.x = _loc6_.x;
                  _loc7_.y = _loc6_.y;
                  this.UpdateGaugePos(_loc7_);
               }
               if(currentFrameLabel == "loop")
               {
                  this.SetEnd();
                  this.m_state = this.STATE_WAIT;
               }
               break;
            case this.STATE_WAIT:
               break;
            case this.STATE_OUT_WAIT:
               if(currentFrameLabel == "end")
               {
                  this.SetOutEnd();
                  this.m_state = this.STATE_END;
               }
         }
      }
      
      public function StartOutAnm() : void
      {
         gotoAndPlay("out");
         this.m_state = this.STATE_OUT_WAIT;
      }
      
      internal function frame24() : *
      {
         stop();
      }
      
      internal function frame37() : *
      {
         stop();
      }
   }
}

